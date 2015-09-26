

#include "common.hpp"
#include "cs-decision-policy.hpp"
#include <cstdlib>

#ifndef NFD_DAEMON_TABLE_CS_UNIFORM_DECISION_POLICY_HPP
#define NFD_DAEMON_TABLE_CS_UNIFORM_DECISION_POLICY_HPP

namespace nfd {
namespace cs{

class UniformDecisionPolicy : public DecisionPolicy
{
public:
  UniformDecisionPolicy()
  {
    std::srand(std::time(NULL));
  };


  virtual bool
  admitPacket(const Data & data)
  {
    return getRand();
  }
private:
  bool
  getRand()
  {
    if (rand() % 100 >= 90) {
      return false;
    }
    return true;
  }
};


} // namespace cs
} // namespace nfd

#endif