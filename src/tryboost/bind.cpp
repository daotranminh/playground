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
#include <map>

#include "Thing.h"

using namespace std;
using namespace placeholders;

int
sum3(int x, int y, int z)
{
  int sum = x + y + z;
  cout << x << '+' << y << '+' << z << '=' << sum << endl;
  return sum;
}


void
mod23(int x, int &y, int &z)
{
  y += x;
  z += y;
  cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
}


void
write_int(ostream &os, int x)
{
  os << x << endl;
}


int main()
{
  // most simple use of bind
  bind(sum3, 1, 2, 3)();
  
  int a = 10;
  int b = 15;
  int c = 20;
  
  cout << "bind and pass the reference of an input parameter" << endl;
  bind(mod23, a, b, c)();
  cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
  
  bind(mod23, a, b, ref(c))();
  cout << "a = " << a << ", b = " << b << ", c = " << c << endl;

  cout << "using placeholders _1, _2,..." << endl;
  bind(mod23, a, _1, _2)(b, c);
  cout << "a = " << a << ", b = " << b << ", c = " << c << endl;

  cout << "using bind in algorithms" << endl;
  list<int> int_list;
  int_list.push_back(2);
  int_list.push_back(2);
  int_list.push_back(2);

  for_each(int_list.begin(), int_list.end(), bind(sum3, _1, 5, 9));
  
  for_each(int_list.begin(), int_list.end(), bind(mod23, 3, 5, _1));
  for_each(int_list.begin(), int_list.end(), bind(write_int, ref(cout), _1));
  
  cout << "using bind with class objects" << endl;
  Thing t1(9);
  
  bind(&Thing::print, t1)();
  bind(&Thing::print, _1)(t1);
  bind(&Thing::write, _1, ref(cout))(t1);
  bind(&Thing::print1arg, _1, _2)(t1, 10);
  bind(&Thing::print2args, _2, _1, _3)(8, t1, 10);
  bind(&Thing::update, _1)(t1);
  bind(&Thing::set_value, _1, 15)(t1);
  bind(&Thing::update, _1)(t1);
  bind(&Thing::update, ref(t1))();
  
  cout << "using bind with algorithms on containers of class objects" << endl;
  bind(&Thing::set_value, _1, 1)(t1);
  Thing t2(2);
  Thing t3(3);
  
  typedef list<Thing> Olist_t;
  Olist_t obj_list = {t1, t2, t3}; // copy construction of list
  
  for_each(obj_list.begin(), obj_list.end(), bind(print_Thing, _1));
  for_each(obj_list.begin(), obj_list.end(), bind(print_Thing_int_int, _1, 20, 30));
  
  for_each(obj_list.begin(), obj_list.end(), bind(&Thing::print, _1));
  for_each(obj_list.begin(), obj_list.end(), bind(&Thing::write, _1, ref(cout)));
  for_each(obj_list.begin(), obj_list.end(), bind(&Thing::print2args, _1, 4, 5));
  for_each(obj_list.begin(), obj_list.end(), bind(&Thing::update, _1));
  for_each(obj_list.begin(), obj_list.end(), bind(&Thing::print, _1));
  
  typedef list<Thing*> Plist_t;
  Plist_t ptr_list = {&t1, &t2, &t3};
  
  for_each(ptr_list.begin(), ptr_list.end(), bind(&Thing::print, _1));
  for_each(ptr_list.begin(), ptr_list.end(), bind(&Thing::write, _1, ref(cout)));
  for_each(ptr_list.begin(), ptr_list.end(), bind(&Thing::print2args, _1, 30, 60));
  for_each(ptr_list.begin(), ptr_list.end(), bind(&Thing::update, _1));
  
  cout << "using bind with map containers" << endl;
  typedef map<int, Thing> Omap_t;
  Omap_t obj_map;
  obj_map[1] = t1;
  obj_map[2] = t2;
  obj_map[3] = t3;
  
  for_each(obj_map.begin(), obj_map.end(),
           bind(&Thing::print,
                bind(&Omap_t::value_type::second, _1)));
  
  for_each(obj_map.begin(), obj_map.end(),
           bind(&Thing::update,
                bind(&Omap_t::value_type::second, _1)));
  
  for_each(obj_map.begin(), obj_map.end(),
           bind(&Thing::print2args,
                bind(&Omap_t::value_type::second, _1), 2, 3));
  
  cout << "using map containers of pointers to class objects" << endl;
  typedef map<int, Thing*> Pmap_t;
  Pmap_t ptr_map;
  ptr_map[1] = &t1;
  ptr_map[2] = &t2;
  ptr_map[3] = &t3;
  
  for_each(ptr_map.begin(), ptr_map.end(),
           bind(&Thing::print,
                bind(&Pmap_t::value_type::second, _1)));
  
  for_each(ptr_map.begin(), ptr_map.end(),
           bind(&Thing::print2args,
                bind(&Pmap_t::value_type::second, _1), 50, 100));
}