#ifndef FOLLOWER_OBJECT_H_
#define FOLLOWER_OBJECT_H_

#include "game_object.h"
#include <glm/ext/vector_float3.hpp>
namespace game
{
  class FollowerObject : public GameObject
  {
  public:
    FollowerObject(const glm::vec3 &position, GLuint texture, GLint num_elements, const glm::vec3 &offset = glm::vec3(0.0f), bool hidden = false);

    void Update(float delta_time) override;
  };
} // namespace game
#endif // FOLLOWER_OBJECT_H_