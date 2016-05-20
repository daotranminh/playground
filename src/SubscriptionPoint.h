//
//  SubscriptionPoint.h
//  playground
//
//  Created by Minh Dao Tran on 20/05/16.
//
//

#ifndef playground_SubscriptionPoint_h
#define playground_SubscriptionPoint_h

#include <memory>

#include "State.h"

class SubscriptionPoint
{
public:
  SubscriptionPoint()
  : state_{std::make_shared<State>()}
  { }
  
  void
  initialize_reading();
  
private:
  std::shared_ptr<State> state_;
};


void
SubscriptionPoint::initialize_reading()
{
  
}

#endif
