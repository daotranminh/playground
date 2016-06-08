//
//  array.cpp
//  playground
//
//  Created by Minh Dao Tran on 08/06/16.
//
//

#include <algorithm>
#include <array>      // Boost.Array is already included in C++11
#include <assert.h>
#include <iostream>


struct add_1 : public std::unary_function<char, void>
{
  void operator()(char &c) { ++c; }
};

typedef std::array<char, 4> array4_t;

array4_t&
vector_advance(array4_t &val)
{
  std::for_each(val.begin(), val.end(), add_1());
  return val;
}

int main()
{
  array4_t val = {{0, 1, 2, 3}};
  
  val = vector_advance(val);
  
  assert (val.size() == 4);
  assert (val[0] == 1);
  
  return 0;
}
