//
//  AsyncServer.cpp
//  playground
//
//  Created by Minh Dao Tran on 14/07/16.
//
//

#include <iostream>
#include <memory>
#include <string>

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

#define MEM_FN(x)      std::bind(&self_type::x, shared_from_this())
#define MEM_FN1(x,y)   std::bind(&self_type::x, shared_from_this(), y)
#define MEM_FN2(x,y,z) std::bind(&self_type::x, shared_from_this(), y, z)

using namespace boost::asio;
using namespace boost::system;

io_service service;
ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001));

class talk_to_client;
typedef std::shared_ptr<talk_to_client> client_ptr;
typedef std::vector<client_ptr> client_array;
client_array clients;


class talk_to_client : public std::enable_shared_from_this<talk_to_client>,
                              boost::noncopyable
{
  typedef talk_to_client self_type;
  
  talk_to_client()
  : sock_(service),
    started_(false),
    timer_(service)
  { }
  
  std::size_t
  read_complete(const boost::system::error_code &err,
                std::size_t bytes)
  {
    if (err) return 0;
    
    bool found = std::find(read_buffer_, read_buffer_ + bytes, '\n') < read_buffer_ + bytes;
    
    return found ? 0 : 1;
  }
  
public:
  typedef boost::system::error_code error_code;
  typedef std::shared_ptr<talk_to_client> ptr;
  
  static ptr new_()
  {
    ptr new_client(new talk_to_client);
    return new_client;
  }
  
  void
  start()
  {
    started_ = true;
    clients.push_back(shared_from_this());
    last_ping = boost::posix_time::microsec_clock::local_time();
    do_read();
  }
  
  void
  stop()
  {
    if (!started_) return;
    started_ = false;
    sock_.close();
    
    ptr self = shared_from_this();
    client_array::iterator it = std::find(clients.begin(), clients.end(), self);
    clients.erase(it);
    set_clients_changed();
  }
  
  bool
  started() const
  {
    return started_;
  }
  
  ip::tcp::socket&
  sock()
  {
    return sock_;
  }
  
  std::string
  usename() const
  {
    return username_;
  }
  
  void
  set_clients_changed()
  {
    clients_changed_ = true;
  }
  
  void
  on_read(const error_code &err,
          std::size_t bytes)
  {
    if (err) stop();
    if (!started()) return;
    
    std::string msg(read_buffer_, bytes);
    
    if (msg.find("login") == 0) on_login(msg);
    else if (msg.find("ping") == 0) on_ping();
    else if (msg.find("ask_clients") == 0) on_clients();
  }
  
  void
  on_login(const std::string &msg)
  {
    std::istringstream in(msg);
    in >> username_ >> username_;
    do_write("login_ok\n");
    set_clients_changed();
  }
  
  void
  on_ping()
  {
    do_write(clients_changed_ ? "ping client_list_changed\n" : "ping ok");
    clients_changed_ = false;
  }
  
  void
  on_clients()
  {
    std::string msg;
    for (client_array::const_iterator it = clients.begin(); it != clients.end(); ++it)
      msg += (*it)->usename() + " ";
    do_write("clients " + msg + "\n");
  }
  
  void
  do_ping()
  {
    do_write("ping\n");
  }
  
  void
  do_ask_clients()
  {
    do_write("ask_clients\n");
  }
  
  void
  on_write(const error_code &err, std::size_t bytes)
  {
    do_read();
  }
  
  void
  do_read()
  {
    async_read(sock_, buffer(read_buffer_),
               MEM_FN2(read_complete, std::placeholders::_1, std::placeholders::_2),
               MEM_FN2(on_read, std::placeholders::_1, std::placeholders::_2));
    
    post_check_ping();
  }

  void
  do_write(const std::string &msg)
  {
    if (!started()) return;
    
    std::copy(msg.begin(), msg.end(), write_buffer_);
    sock_.async_write_some(buffer(write_buffer_, msg.size()),
                           MEM_FN2(on_write, std::placeholders::_1, std::placeholders::_2));
  }
  
  void
  on_check_ping()
  {
    boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
    
    if ((now - last_ping).total_microseconds() > 5000)
      stop();
    last_ping = boost::posix_time::microsec_clock::local_time();
  }
  
  void
  post_check_ping()
  {
    timer_.expires_from_now(boost::posix_time::milliseconds(5000));
    timer_.async_wait(MEM_FN(on_check_ping));
  }
  
private:
  ip::tcp::socket sock_;
  enum { max_msg = 1024 };
  char read_buffer_[max_msg];
  char write_buffer_[max_msg];
  bool started_;
  std::string username_;
  deadline_timer timer_;
  boost::posix_time::ptime last_ping;
  bool clients_changed_;
};

void
handle_accept(talk_to_client::ptr client,
              const boost::system::error_code &err)
{
  client->start();
  talk_to_client::ptr new_client = talk_to_client::new_();
  acceptor.async_accept(new_client->sock(), std::bind(handle_accept, new_client, std::placeholders::_1));
}

int main(int argc, char *argv[])
{
  talk_to_client::ptr client = talk_to_client::new_();
  acceptor.async_accept(client->sock(), std::bind(handle_accept, client, std::placeholders::_1));
  service.run();
}