//
//  program_options.cpp
//  playground
//
//  Created by Minh Dao Tran on 08/06/16.
//
//

#include <iostream>
#include <vector>
#include <string>

#include <boost/variant.hpp>

struct db_sum_visitor : public boost::static_visitor<double>
{
  double operator()(int value) const
  {
    return value;
  }
  
  double operator()(float value) const
  {
    return value;
  }
  
  double operator()(const std::string& /*value*/) const
  {
    return 0.0;
  }
};

int main()
{
  typedef boost::variant<boost::blank, int, const char*, std::string> my_var_t;
  
  std::vector<my_var_t> some_values;
  some_values.push_back(10);
  some_values.push_back("Hello there!");
  some_values.push_back(std::string("Wow!"));
  
  std::string &s = boost::get<std::string>(some_values.back());
  s += " That is great!\n";
  std::cout << s;
  
  // to represent empty state
  my_var_t var;
  assert(var.which() == 0);
  
  var = "Hello, dear reader";
  assert(var.which() != 0);
  
  // **************************************************************************
  // a safer way to work with containers storing multiple chosen types
  typedef boost::variant<int, float, std::string> cell_t;
  typedef std::vector<cell_t> db_row_t;
  
  db_row_t row;
  row.push_back(10);
  row.push_back(10.1f);
  row.push_back("Hello again");
  
  double res = 0.0;
  for (db_row_t::const_iterator it = row.begin(); it != row.end(); ++it)
  {
    res += boost::apply_visitor(db_sum_visitor(), *it);
  }
  
  std::cout << "Sum of arithmetic types in row is "
  << res << std::endl;
  
  return 0;
}
