//
//  ASyncEchoServer.cpp
//  playground
//
//  Created by Minh Dao Tran on 12/07/16.
//
//

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

#define MEM_FN(x)      std::bind(&self_type::x, shared_from_this())
#define MEM_FN1(x,y)   std::bind(&self_type::x, shared_from_this(), y)
#define MEM_FN2(x,y,z) std::bind(&self_type::x, shared_from_this(), y, z)

using namespace boost::asio;
using namespace boost::system;
using namespace std::placeholders;

io_service service;

class talk_to_client : public std::enable_shared_from_this<talk_to_client>,
                              boost::noncopyable
{
  typedef talk_to_client self_type;
  
  talk_to_client()
  : sock_(service),
    started_(false)
  { }
  
public:
  typedef boost::system::error_code error_code;
  typedef std::shared_ptr<talk_to_client> ptr;
  
  void
  start()
  {
    started_ = true;
    do_read();
  }
  
  static ptr new_()
  {
    ptr new_(new  talk_to_client);
    return new_;
  }
  
  void
  stop()
  {
    if (!started_)
      return;
    
    started_ = false;
    sock_.close();
  }
  
  ip::tcp::socket&
  sock()
  {
    return sock_;
  }
  
private:
  void
  do_write(const std::string &msg)
  {
    if (!started())
      return;
    
    std::copy(msg.begin(), msg.end(), write_buffer_);
    sock_.async_write_some(buffer(write_buffer_, msg.size()), MEM_FN2(on_write, std::placeholders::_1, std::placeholders::_2));
  }
  
  void
  do_read()
  {
    async_read(sock_, buffer(read_buffer_),
               MEM_FN2(read_complete, std::placeholders::_1, std::placeholders::_2),
               MEM_FN2(on_read, std::placeholders::_1, std::placeholders::_2));
  }
  
  std::size_t
  read_complete(const error_code &err,
                std::size_t bytes)
  {
    if (err) return 0;
    
    bool found = std::find(read_buffer_, read_buffer_+bytes, '\n') < read_buffer_ + bytes;
    
    return found ? 0 : 1;
  }
  
  void
  on_read(const error_code &err,
          std::size_t bytes)
  {
    if (!err)
    {
      std::string msg(read_buffer_, bytes);
      do_write(msg + "\n");
    }
  }
  
  void
  on_write(const error_code &err,
           std::size_t bytes)
  {
    do_read();
  }
  
  
  bool
  started()
  {
    return started_;
  }
  
private:
  ip::tcp::socket sock_;
  enum { max_msg = 1024 };
  char read_buffer_[max_msg];
  char write_buffer_[max_msg];
  bool started_;
};


ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001));

void
handle_accept(talk_to_client::ptr client,
              const error_code &err)
{
  client->start();
  talk_to_client::ptr new_client = talk_to_client::new_();
  
  acceptor.async_accept(new_client->sock(), std::bind(handle_accept, new_client, std::placeholders::_1));
}

int main()
{
  talk_to_client::ptr new_client = talk_to_client::new_();
  
  acceptor.async_accept(new_client->sock(), std::bind(handle_accept, new_client, std::placeholders::_1));

  service.run();
}