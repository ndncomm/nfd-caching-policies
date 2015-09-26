#include "common.hpp"

#ifndef NFD_DAEMON_TABLE_CS_DECISION_POLICY_HPP
#define NFD_DAEMON_TABLE_CS_DECISION_POLICY_HPP

namespace nfd {
namespace cs{

/*
 * \brief Represents the CS cache decision policy.
 */
class DecisionPolicy
{
public:
  DecisionPolicy() {};


  /**
   * \brief Decides if to cache an incoming data packet.
   *
   * Returns true if the packet should be cached, false otherwise.
   */
  virtual bool admitPacket(const Data & data) = 0;
};

} // namespace cs
} // namespace nfd


#endif
