
#include "cs-lcd-decision-policy.hpp"

#include "../../../utils/ndn-ns3-packet-tag.hpp"
#include "../../../utils/ndn-fw-hop-count-tag.hpp"
#include <ndn-cxx/tag-host.hpp>

namespace nfd {
namespace cs{

// LcdDecisionPolicy::

bool
LcdDecisionPolicy::admitPacket(const Data & data)
{
  using ns3::ndn::FwHopCountTag;
  using ns3::ndn::Ns3PacketTag;

  uint32_t hopCount = 0;

  auto ns3PacketTag = data.getTag<ns3::ndn::Ns3PacketTag>();
  if (ns3PacketTag != nullptr) {
    FwHopCountTag hopCountTag;
    if (ns3PacketTag->getPacket()->PeekPacketTag(hopCountTag)) {
      hopCount = hopCountTag.Get();
    }
  }

  if (hopCount == 1) {
    return true;
  }
  return false;
}

} // cs namespace
} // nfd namespace
