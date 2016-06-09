//
//  bind.cpp
//  playground
//
//  Created by Minh Dao Tran on 08/06/16.
//
//

// Instructions from: http://www.umich.edu/~eecs381/handouts/bind.pdf

#include <functional>
#include <iostream>
#include <list>

#include "Thing.h"

using namespace std::placeholders;

int
sum3(int x, int y, int z)
{
  int sum = x + y + z;
  std::cout << x << '+' << y << '+' << z << '=' << sum << std::endl;
  return sum;
}


void
mod23(int x, int &y, int &z)
{
  y += x;
  z += y;
  std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
}


void
write_int(std::ostream &os, int x)
{
  os << x << std::endl;
}


int main()
{
  // most simple use of bind
  std::bind(sum3, 1, 2, 3)();
  
  int a = 10;
  int b = 15;
  int c = 20;
  
  // bind and pass the reference of an input parameter
  std::bind(mod23, a, b, c)();
  std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
  
  std::bind(mod23, a, b, std::ref(c))();
  std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;

  // using placeholders _1, _2,...
  std::bind(mod23, a, _1, _2)(b, c);
  std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;

  // using bind in algorithms
  std::list<int> int_list;
  int_list.push_back(2);
  int_list.push_back(2);
  int_list.push_back(2);

  for_each(int_list.begin(), int_list.end(), std::bind(sum3, _1, 5, 9));
  
  for_each(int_list.begin(), int_list.end(), std::bind(mod23, 3, 5, _1));
  for_each(int_list.begin(), int_list.end(), std::bind(write_int, std::ref(std::cout), _1));
  
  // using bind with class objects
  Thing t1(9);
  
  std::bind(&Thing::print, t1)();
  std::bind(&Thing::print, _1)(t1);
  std::bind(&Thing::write, _1, std::ref(std::cout))(t1);
  std::bind(&Thing::print1arg, _1, _2)(t1, 10);
  std::bind(&Thing::print2args, _2, _1, _3)(8, t1, 10);
  std::bind(&Thing::update, _1)(t1);
  std::bind(&Thing::set_value, _1, 15)(t1);
  std::bind(&Thing::update, _1)(t1);
  std::bind(&Thing::update, std::ref(t1))();
  
  // using bind with algorithms on containers of class objects
  
}