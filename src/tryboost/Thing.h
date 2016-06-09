//
//  Thing.h
//  playground
//
//  Created by Minh Dao Tran on 09/06/16.
//
//

#ifndef playground_Thing_h
#define playground_Thing_h

#include <iostream>

class Thing
{
public:
  Thing(int id = 0)
  : id_{id}
  { }
  
  void
  print() const
  {
    std::cout << "Thing " << id_ << std::endl;
  }
  
  void
  write(std::ostream &os) const
  {
    os << "Thing " << id_ << " written to stream" << std::endl;
  }
  
  void
  print1arg(int i) const
  {
    std::cout << "Thing " << id_ << " with arg " << i << std::endl;
  }
  
  void
  print2args(int i, int j) const
  {
    std::cout << "Thing " << id_ << " with args " << i << ' ' << j << std::endl;
  }
  
  int
  get_value() const
  {
    return id_;
  }
  
  void
  set_value(int id)
  {
    id_ = id;
  }
  
  void
  update()
  {
    id_++;
    std::cout << "Thing updated to " << id_ << std::endl;
  }
  
private:
  int id_;
};


std::ostream&
operator<<(std::ostream &os, const Thing &t)
{
  os << "Thing: " << t.get_value();
  return os;
}


void
print_Thing(Thing t)
{
  t.print();
}


void
print_Thing_const_ref(const Thing &t)
{
  t.print();
}


void
print_int_Thing(int i, Thing t)
{
  std::cout << "print_int_Thing " << i << ' ' << t << std::endl;
}


void
print_Thing_int(Thing t, int i)
{
  std::cout << "print_Thing_int " << t << ' ' << i << std::endl;
}

void
print_Thing_int_int(Thing t, int i, int j)
{
  std::cout << "print_Thing_int_int " << t << ' ' << i << ' ' << j << std::endl;
}

#endif
