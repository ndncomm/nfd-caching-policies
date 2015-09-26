

#include "common.hpp"
#include "cs-decision-policy.hpp"

namespace nfd {
namespace cs{

class UniformDecisionPolicy : DecisionPolicy
{
public:
  UniformDecisionPolicy()
  {
    srand(time(NULL));
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
