//
//  RDFtext.h
//  playground
//
//  Created by Minh Dao Tran on 20/05/16.
//
//

#ifndef playground_RDFtext_h
#define playground_RDFtext_h

#include <iostream>
#include <string>

struct RDFtext
{
  std::string s;
  std::string p;
  std::string o;
  
  RDFtext(const std::string &s,
          const std::string &p,
          const std::string &o)
  : s{s}, p{p}, o{o}
  { }
};

std::ostream&
operator<<(std::ostream &os,
           const RDFtext &rdft)
{
  return os << "(" << rdft.s << ", " << rdft.p << ", " << rdft.o << ")";
}

#endif
