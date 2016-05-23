#include "rxcpp/rx.hpp"

#include <cctype>
#include <clocale>

#include <iostream>
#include <string>
#include <vector>

#include "RDFtextFileReader.h"

int main()
{
/*  rxcpp::observable<RDFtext> input_stream =
  rxcpp::observable<>::create<RDFtext>(
    [](rxcpp::subscriber<RDFtext> subscriber)
    {
      RDFtextFileReader reader;
      auto items = reader.take();
      for (auto item : items)
        subscriber.on_next(item);
    });
  
  input_stream.subscribe
  (
   [](const RDFtext &triple){ std::cout << "On next " << triple << std::endl; },
   [](){ std::cout << "On complete" << std::endl; }
  );*/
  
  rxcpp::subjects::subject<std::string> subj;
  
  rxcpp::subscriber<std::string> sub = subj.get_subscriber();
  rxcpp::observable<std::string> obs = subj.get_observable();
  
  obs.subscribe
  (
   [](std::string s){ std::cout << "On next with " << s << std::endl; },
   [](){ std::cout << "On completed here!" << std::endl;}
  );
  
  sub.on_next("aaa");
  sub.on_next("bbb");
  sub.on_next("ccc");
  sub.on_completed();
}

