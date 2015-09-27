#include "cs-uniform-decision-policy.hpp"
#include <cstdlib>

namespace nfd {
namespace cs{

UniformDecisionPolicy::
UniformDecisionPolicy(int acceptRatio)
{
  std::srand(std::time(NULL));

  // Check if accept ratio is in the correct range. If it's not: Set it to 100%.
  if (acceptRatio >= 0 && acceptRatio <= 100){
    m_acceptRatio = acceptRatio;
  }
  else {
    m_acceptRatio = 100;
  }

  m_policyName = std::string("Uniform");
};


bool
UniformDecisionPolicy::getRand()
{
  if (rand() % 100 < m_acceptRatio) {
    return true;
  }
  return false;
}

bool
UniformDecisionPolicy::admitPacket(const Data & data)
{
  return getRand();
}

}
}
