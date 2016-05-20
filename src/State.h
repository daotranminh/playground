//
//  State.h
//  playground
//
//  Created by Minh Dao Tran on 20/05/16.
//
//

#ifndef playground_State_h
#define playground_State_h

#include "rxcpp/rx.hpp"
#include "RDFtextFileReader.h"

struct State
{
  rxcpp::subjects::subject<RDFtext> data_subject_;
  RDFtextFileReader reader_;
  
  bool init_reading_done_;
  
  State()
  : init_reading_done_{false}
  { }
};

#endif
