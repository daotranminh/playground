//
//  optional.cpp
//  playground
//
//  Created by Minh Dao Tran on 08/06/16.
//
//

#include <iostream>
#include <stdlib.h>

#include <boost/optional.hpp>

class locked_device
{
  // explicit keyword: to prevent implicit conversion of function parameters
  // see: stackoverflow.com/questions/121162/what-does-the-explicit-keyword-in-c-mean
  explicit locked_device(const char* /*param*/)
  {
    std::cout << "Device is now locked!" << std::endl;
  }
    
    
public:
  ~locked_device()
  {
    // releasing device lock
  }
    
  void
  use()
  {
    std::cout << "Success!" << std::endl;
  }
    
  static boost::optional<locked_device>
  try_lock_device()
  {
    if (rand() % 2) return boost::none;
    return locked_device("device name");
  }
};

int main()
{
  srandom(21);
  
  for (auto i = 0; i < 10; ++i)
  {
    boost::optional<locked_device> t = locked_device::try_lock_device();
    
    if (t)
    {
      t->use();
      return 0;
    }
    else
    {
      std::cout << "...trying again" << std::endl;
    }
  }
  
  std::cout << "Failure!" << std::endl;
  return 1;
}