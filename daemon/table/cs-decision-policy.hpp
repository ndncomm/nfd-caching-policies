

#include "common.hpp"

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
