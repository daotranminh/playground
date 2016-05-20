#include "rxcpp/rx.hpp"

#include <cctype>
#include <clocale>

#include <iostream>
#include <vector>

#include "RDFtextFileReader.h"

int main()
{
  rxcpp::observable<RDFtext> input_stream =
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
  );
}

