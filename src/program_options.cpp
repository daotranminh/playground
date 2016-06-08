//
//  program_options.cpp
//  playground
//
//  Created by Minh Dao Tran on 07/06/16.
//
//

#include <iostream>

#include <boost/program_options.hpp>
#include <boost/program_options/errors.hpp>

namespace opt = boost::program_options;

int main(int argc, char *argv[])
{
  opt::options_description desc("All options");
  
  desc.add_options()
  ("help", "produce help message")
  ("apples,a", opt::value<int>()->default_value(10), "how many apples do you have")
  ("oranges,o", opt::value<int>()->default_value(20), "how many oranges do you have")
  ("name,n", opt::value<std::string>(), "your name")
  ;
  
  opt::variables_map vm;
  
  opt::store(opt::parse_command_line(argc, argv, desc), vm);
  opt::notify(vm);
  
  if (vm.count("help"))
  {
    std::cout << desc << std::endl;
    return 1;
  }
  
  std::string config_file_name("/Users/minhdt/Documents/repositories/playground/apples_oranges.cfg");
  try
  {
    opt::store(opt::parse_config_file<char>(config_file_name.c_str(), desc), vm);
  }
  catch (const opt::reading_file &e)
  {
    std::cout << "Failed to open file '" << config_file_name << "'"
    << e.what() << std::endl;
  }
  
  if (vm.count("name"))
  {
    std::cout << "Hi " << vm["name"].as<std::string>() << std::endl;
  }
  
  std::cout << "Fruits count:"
    << vm["apples"].as<int>() + vm["oranges"].as<int>()
    << std::endl;
}
