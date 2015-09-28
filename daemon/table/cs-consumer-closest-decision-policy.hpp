
#include "common.hpp"
#include "cs-decision-policy.hpp"
#include "ns3/random-variable-stream.h"

#ifndef NFD_DAEMON_TABLE_CS_CONSUMER_CLOSEST_DECISION_POLICY_HPP
#define NFD_DAEMON_TABLE_CS_CONSUMER_CLOSEST_DECISION_POLICY_HPP

namespace nfd {
namespace cs{

class ConsumerClosestDecisionPolicy : public DecisionPolicy
{
public:
  ConsumerClosestDecisionPolicy()
  {
    m_policyName = std::string("ConsumerClosest");
    m_ranVar = ns3::CreateObject<ns3::UniformRandomVariable>();
  };

  virtual bool admitPacket(const Data & data);

private:
  bool randAccept(int hopCount);

private:
  ns3::Ptr<ns3::UniformRandomVariable>  m_ranVar;
};


} // namespace cs
} // namespace nfd

#endif