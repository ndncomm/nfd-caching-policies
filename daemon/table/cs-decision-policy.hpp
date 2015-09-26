#include "common.hpp"

#ifndef NFD_DAEMON_TABLE_CS_DECISION_POLICY_HPP
#define NFD_DAEMON_TABLE_CS_DECISION_POLICY_HPP

namespace nfd {
namespace cs{

class DecisionPolicy
{
public:
  DecisionPolicy() {};
  virtual bool admitPacket(const Data & data) = 0;
};


} // namespace cs
} // namespace nfd

#endif