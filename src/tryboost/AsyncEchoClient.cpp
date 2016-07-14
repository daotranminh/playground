//
//  AsyncEchoClient.cpp
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

using namespace boost::asio;
using namespace boost::system;
using namespace std::placeholders;

#define MEM_FN(x)      std::bind(&self_type::x, shared_from_this())
#define MEM_FN1(x,y)   std::bind(&self_type::x, shared_from_this(), y)
#define MEM_FN2(x,y,z) std::bind(&self_type::x, shared_from_this(), y, z)

io_service service;

class talk_to_svr : public std::enable_shared_from_this<talk_to_svr>,
                           boost::noncopyable
{
  typedef talk_to_svr self_type;
  
  
  talk_to_svr(const std::string &message)
  : sock_(service),
    started_(true),
    message_(message)
  { }

  
  void
  start(ip::tcp::endpoint ep)
  {
    sock_.async_connect(ep, MEM_FN1(on_connect, std::placeholders::_1));
  }
  
  
  void
  on_connect(const error_code &err)
  {
    if (!err)
      do_write(message_ + "\n");
    else
      stop();
  }
  
  void
  do_write(const std::string &msg)
  {
    if (!started())
      return;
    
    std::copy(msg.begin(), msg.end(), write_buffer_);
    sock_.async_write_some(buffer(write_buffer_, msg.size()), MEM_FN2(on_write, std::placeholders::_1, std::placeholders::_2));
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
      std::string copy(read_buffer_, bytes-1);
      std::cout << "Server echoed our " << message_ << ": " << (copy == message_ ? "OK" : "FAIL") << std::endl;
    }
    stop();
  }
  
public:
  typedef boost::system::error_code error_code;
  typedef std::shared_ptr<talk_to_svr> ptr;
  
  static ptr
  start(ip::tcp::endpoint ep,
        const std::string &message)
  {
    ptr new_(new talk_to_svr(message));
    new_->start(ep);
    return new_;
  }
  
  void
  stop()
  {
    if (!started_) return;
    started_ = false;
    sock_.close();
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
  std::string message_;
};

int main(int argc, char *argv[])
{
  ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8001);;
  
  std::vector<std::string> messages{"Test 1", "Test 2"};
  
  for (auto it = messages.begin(); it != messages.end(); ++it)
  {
    talk_to_svr::start(ep, *it);
    boost::this_thread::sleep(boost::posix_time::millisec(100));
  }
  
  service.run();
}