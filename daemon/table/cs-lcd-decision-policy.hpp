
#include "common.hpp"
#include "cs-decision-policy.hpp"

#ifndef NFD_DAEMON_TABLE_CS_LCD_DECISION_POLICY_HPP
#define NFD_DAEMON_TABLE_CS_LCD_DECISION_POLICY_HPP

namespace nfd {
namespace cs{

class LcdDecisionPolicy : public DecisionPolicy
{
public:
  LcdDecisionPolicy()
  {
  };

  virtual bool admitPacket(const Data & data);

private:

};


} // namespace cs
} // namespace nfd

#endif