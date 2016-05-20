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

#include "rxcpp/rx.hpp"

#include "RDFtext.h"
#include "State.h"

class SubscriptionPoint
{
public:
  SubscriptionPoint()
  : state_{std::make_shared<State>()}
  { }
  
  void
  initialize_reading();
  
  rxcpp::observable<RDFtext>
  create_observable();
  
private:
  std::shared_ptr<State> state_;
};


void
SubscriptionPoint::initialize_reading()
{
  if (!state_->init_reading_done_)
  {
    typename rxcpp::subjects::subject<RDFtext>::subscriber_type subscriber =
    state_->data_subject_.get_subscriber();
    
    auto samples = state_->reader_.take();
    for (auto sample : samples)
      subscriber.on_next(sample);
    
    state_->init_reading_done_ = true;
  }
}

rxcpp::observable<RDFtext>
SubscriptionPoint::create_observable()
{
  SubscriptionPoint me = *this;
  
  return rxcpp::observable<>::create<RDFtext>
  (
   [me](rxcpp::subscriber<RDFtext> subscriber){
     //const_cast<SubscriptionPoint&>(me).initialize_reading();
     
     auto samples = me.state_->reader_.take();
     for (auto sample : samples)
       subscriber.on_next(sample);
     
     /*rxcpp::composite_subscription subscription =
       me.state_->data_subject_.get_observable().subscribe(subscriber);
     
     return subscription;*/
   });
}


#endif
