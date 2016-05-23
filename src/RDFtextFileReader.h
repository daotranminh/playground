//
//  RDFtextFileReader.h
//  playground
//
//  Created by Minh Dao Tran on 20/05/16.
//
//

#ifndef playground_RDFtextFileReader_h
#define playground_RDFtextFileReader_h

#include <fstream>
#include <vector>

#include "RDFtext.h"

class RDFtextFileReader
{
public:
  RDFtextFileReader()
  : m_File{"/Users/minhdt/Documents/softwares/playground/sample.txt"}
  { }
  
  std::vector<RDFtext>
  take()
  {
    std::vector<RDFtext> res;
    
    if (m_File.is_open())
    {
      while (!m_File.eof())
      {
        std::string line;
        std::getline(m_File, line);
      
        auto pos1 = line.find(",");
        auto pos2 = line.find(",", pos1+1);
      
        std::string s = line.substr(0, pos1);
        std::string p = line.substr(pos1+1, pos2-pos1-1);
        std::string o = line.substr(pos2+1);
        
        //std::cout << s << p << o << std::endl;

        res.push_back(RDFtext(s,p,o));
      }
    }
    return res;
  }
  
private:
  std::ifstream m_File;
};

#endif
