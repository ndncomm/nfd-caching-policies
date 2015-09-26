
#include "common.hpp"
#include "cs-decision-policy.hpp"

#ifndef NFD_DAEMON_TABLE_CS_LCD_DECISION_POLICY_HPP
#define NFD_DAEMON_TABLE_CS_LCD_DECISION_POLICY_HPP

namespace nfd {
namespace cs{

/**
 * \brief A cache decision policy based on Leave a Copy Down (LCD).
 *
 * Only caches content one hop down from the sender (either content repository or cache).
 */
class LcdDecisionPolicy : public DecisionPolicy
{
public:
  LcdDecisionPolicy()
  {
    m_policyName = std::string("Lcd");
  };

  virtual bool admitPacket(const Data & data);

private:

};


} // namespace cs
} // namespace nfd

#endif
