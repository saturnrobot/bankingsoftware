#ifndef BULLET_H_
#define BULLET_H_
#include "entity.h"
#include "../object/colliders/ray_collider.h"
#include <glm/gtx/rotate_vector.hpp>

namespace game
{
  class Bullet : public Entity
  {

  public:
    Bullet(const glm::vec3 &position, GLuint texture, GLint num_elements, RayCollider *collider, EffectObject *collision_effect, float speed, float alive_time, bool hidden = false);
    Bullet(const Bullet &bullet);
    // Update function for moving the player object around
    void Update(float delta_time) override;
    inline virtual RayCollider *GetCollider() override { return static_cast<RayCollider *>(collider_); }

  protected:
    void Collision(Entity *collider) override;

  private:
    float spawn_time_;
    float alive_time_;
  };

} // namespace game

#endif // BULLET_H_