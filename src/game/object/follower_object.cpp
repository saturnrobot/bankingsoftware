#include "follower_object.h"
#include "game_object.h"
#include <glm/fwd.hpp>
#include <iostream>
namespace game
{
  FollowerObject::FollowerObject(const glm::vec3 &position, GLuint texture, GLint num_elements, const glm::vec3 &offset, bool hidden)
      : GameObject(position, texture, num_elements, hidden)
  {
    position_ = position + offset;
  }

  void FollowerObject::Update(float delta_time)
  {
    rotation_ += delta_time * 1000;
  }
}