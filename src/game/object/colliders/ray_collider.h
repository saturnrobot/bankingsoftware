#ifndef RAY_COLLIDER_H_
#define RAY_COLLIDER_H_
#include "../collider.h"
#include "circle_collider.h"
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

namespace game
{
  class RayCollider : public Collider
  {
  public:
    RayCollider(const std::string& tag, const glm::vec3 &direction = glm::vec3(0));
    virtual bool CheckCollision(Collider *collider) const override;
    virtual bool CheckCollision(CircleCollider *collider) const;
    inline glm::vec3 GetDirection(void) const { return direction_; }
    inline void SetDirection(const glm::vec3 &direction) { direction_ = direction; }

    inline virtual RayCollider* clone(void) override { return new RayCollider(*this); }
    inline virtual RayCollider* visit(void) override { return this; }

  protected:
    glm::vec3 direction_;
  };
} // namespace game

#endif // RAY_COLLIDER_H_