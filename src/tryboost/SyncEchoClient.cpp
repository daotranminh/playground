//
//  SyncEchoClient.cpp
//  playground
//
//  Created by Minh Dao Tran on 17/06/16.
//
//

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using namespace boost::asio;
using namespace boost::system;
using namespace std::placeholders;

io_service service;
ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8001);

std::size_t
read_complete(char *buf,
              const error_code &err,
              std::size_t bytes)
{
  if (err) return 0;
  
  bool found = std::find(buf, buf+bytes, '\n') < buf + bytes;
  
  return found ? 0 : 1;
}

void
sync_echo(std::string msg)
{
  msg += '\n';
  ip::tcp::socket sock(service);
  sock.connect(ep);
  sock.write_some(buffer(msg));
  
  char buf[1024];
  
  int bytes = read(sock, buffer(buf),
                   std::bind(read_complete, buf, std::placeholders::_1, std::placeholders::_2));
  
  std::string copy(buf, bytes - 1);
  msg = msg.substr(0, msg.size() - 1);
  
  std::cout << "Server echoed our " << msg << ": "
            << (copy == msg ? "OK" : "FAIL")
            << std::endl;
  
  sock.close();
}

int main()
{
  std::vector<std::string> messages{"Test 1", "Test 2"};
  
  boost::thread_group threads;
  for (auto it = messages.begin(); it != messages.end(); ++it)
  {
    threads.create_thread(std::bind(sync_echo, *it));
    boost::this_thread::sleep(boost::posix_time::millisec(100));
  }
  
  threads.join_all();
}