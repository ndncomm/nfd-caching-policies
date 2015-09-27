
#include "cs-producer-closest-decision-policy.hpp"

#include "../../../utils/ndn-ns3-packet-tag.hpp"
#include "../../../utils/ndn-fw-hop-count-tag.hpp"
#include <ndn-cxx/tag-host.hpp>
#include <cmath>

namespace nfd {
namespace cs{

bool
ProducerClosestDecisionPolicy::admitPacket(const Data & data)
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
  return randAccept(hopCount);
}

bool
ProducerClosestDecisionPolicy::randAccept(int hopCount)
{
  if (hopCount == 0) {
    return true;
  }

  double acceptRatio = 1 / pow(2.0, double(hopCount - 1));

  if (m_ranVar.GetValue(double(0), double(1.0)) <= acceptRatio) {
    return true;
  }
  return false;
}


}// cs
}// nfd