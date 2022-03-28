#include "collider.h"

namespace game
{
  Collider::Collider(const std::string &tag, const glm::vec3 *position) : position_(position), tag_(tag)
  {
  }

  Collider::~Collider()
  {
  }
}