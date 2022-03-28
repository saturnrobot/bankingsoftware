#include "circle_collider.h"
#include <iostream>

namespace game
{
  CircleCollider::CircleCollider(const std::string &tag, float radius) : Collider(tag), radius_(radius)
  {
  }

  bool CircleCollider::CheckCollision(Collider *collider) const
  {
    return CircleCollider::CheckCollision(static_cast<CircleCollider *>(collider));
  }

  bool CircleCollider::CheckCollision(CircleCollider *collider) const
  {
    float distance = glm::length(*position_ - *collider->GetPosition());
    return distance < radius_ + collider->GetRadius();
  }
}