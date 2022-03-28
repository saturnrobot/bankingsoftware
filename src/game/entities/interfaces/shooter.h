#ifndef SHOOTER_H_
#define SHOOTER_H_
#include "../bullet.h"
#include "../../object/colliders/ray_collider.h"
#include <vector>

namespace game
{
  class Shooter
  {

  public:
    Shooter(Bullet *bullet, float cooldown);
    ~Shooter();
    virtual void DeleteShots();
    virtual void UpdateShots(float delta_time);
    virtual void RenderShots(Shader &shader);
    virtual void CheckBulletCollisions(Entity* shooter, std::vector<Entity *> cols);
    virtual void Shoot(const glm::vec3 &position, float rotation);
    void ReduceCooldown(float amount = 0.05f);

  protected:
    Bullet *bullet_;
    std::vector<Bullet *> bullets_;
  private:
    float time_since_last_shot_;
    float cooldown_;
  };

} // namespace game

#endif // SHOOTER_H_