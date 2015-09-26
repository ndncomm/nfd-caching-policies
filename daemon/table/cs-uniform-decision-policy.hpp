#include "common.hpp"
#include "cs-decision-policy.hpp"

#ifndef NFD_DAEMON_TABLE_CS_UNIFORM_DECISION_POLICY_HPP
#define NFD_DAEMON_TABLE_CS_UNIFORM_DECISION_POLICY_HPP

namespace nfd {
namespace cs{

class UniformDecisionPolicy : public DecisionPolicy
{
public:
  /**
   * /brief Makes a caching decision based on a fixed uniform random probability.
   *
   * The parameter acceptRatio specifies the probability in %. It should be an Integer between 0 and 100.
   *
   */
  UniformDecisionPolicy(int acceptRatio);

  virtual bool admitPacket(const Data & data);

private:
  bool getRand();

private:
  int m_acceptRatio;
};


} // namespace cs
} // namespace nfd

#endif
