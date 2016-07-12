//
//  SyncServer.cpp
//  playground
//
//  Created by Minh Dao Tran on 12/07/16.
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

std::size_t
read_complete(char *buff,
              const error_code &err,
              std::size_t bytes)
{
  if (err) return 0;
  
  bool found = std::find(buff, buff+bytes, '\n') < buff + bytes;
  
  return found ? 0 : 1;
}


void
handle_connections()
{
  ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8001));
  
  char buff[1024];
  
  while (true)
  {
    ip::tcp::socket sock(service);
    acceptor.accept(sock);
    
    int bytes = read(sock, buffer(buff),
                     std::bind(read_complete, buff, std::placeholders::_1, std::placeholders::_2));
    
    std::string msg(buff, bytes);
    
    std::cout << "Received: " << msg << std::endl;
    
    sock.write_some(buffer(msg));
    sock.close();
  }
}


int main(int argc,
         char *argv[])
{
  handle_connections();
}