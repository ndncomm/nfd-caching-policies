
#include "common.hpp"
#include "cs-decision-policy.hpp"
#include "ns3/random-variable-stream.h"

#ifndef NFD_DAEMON_TABLE_CS_PRODUCER_CLOSEST_DECISION_POLICY_HPP
#define NFD_DAEMON_TABLE_CS_PRODUCER_CLOSEST_DECISION_POLICY_HPP

namespace nfd {
namespace cs{

class ProducerClosestDecisionPolicy : public DecisionPolicy
{
public:
  ProducerClosestDecisionPolicy()
  {
    m_policyName = std::string("ProducerClosest");
  };

  virtual bool admitPacket(const Data & data);

private:
  bool randAccept(int hopCount);

private:
  ns3::UniformRandomVariable m_ranVar;
};


} // namespace cs
} // namespace nfd

#endif