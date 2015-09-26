#include "common.hpp"
#include "cs-decision-policy.hpp"

#ifndef NFD_DAEMON_TABLE_CS_UNIFORM_DECISION_POLICY_HPP
#define NFD_DAEMON_TABLE_CS_UNIFORM_DECISION_POLICY_HPP

namespace nfd {
namespace cs{

class UniformDecisionPolicy : public DecisionPolicy
{
public:
  /** /brief acceptRatio shoube a an integer
      between 0 to 100
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