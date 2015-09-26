#include "cs-uniform-decision-policy.hpp"
#include <cstdlib>

namespace nfd {
namespace cs{

UniformDecisionPolicy::
UniformDecisionPolicy(int acceptRatio):
  m_acceptRatio(acceptRatio)
{
  std::srand(std::time(NULL));
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