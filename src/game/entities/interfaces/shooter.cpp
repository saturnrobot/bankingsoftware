#include "shooter.h"
#include <glm/gtx/rotate_vector.hpp>

namespace game
{
  Shooter::Shooter(Bullet *bullet, float cooldown)
  {
    bullet_ = bullet;
    cooldown_ = cooldown;
    time_since_last_shot_ = cooldown + 1;
  }

  Shooter::~Shooter()
  {
    Shooter::DeleteShots();
  }

  void Shooter::DeleteShots()
  {
    bullets_.clear();
    delete bullet_;
  }

  void Shooter::UpdateShots(float delta_time)
  {
    time_since_last_shot_ += delta_time;
    for (std::vector<Bullet *>::iterator bullet = bullets_.begin(); bullet != bullets_.end();)
    {
      (*bullet)->Update(delta_time);
      if ((*bullet)->MarkedForDeletion())
      {
        bullets_.erase(bullet);
      }
      else
      {
        ++bullet;
      }
    }
  }

  void Shooter::RenderShots(Shader &shader)
  {
    for (Bullet *bullet : bullets_)
    {
      bullet->Render(shader);
    }
  }

  void Shooter::CheckBulletCollisions(Entity *shooter, std::vector<Entity *> cols)
  {
    for (Entity *col : cols)
    {
      for (Bullet *bullet : bullets_)
      {
        if (col != shooter)
        {
          bullet->CheckCollisionEntity(col);
        }
      }
    }
  }

  void Shooter::Shoot(const glm::vec3 &position, float rotation)
  {
    if (cooldown_ < time_since_last_shot_)
    {
      time_since_last_shot_ = 0;
      Bullet *bulletToSpawn = new Bullet(*bullet_);
      bulletToSpawn->SetPosition(position);
      bulletToSpawn->SetRotation(rotation);
      bulletToSpawn->GetCollider()->Init(&(bulletToSpawn->GetPosition()));
      bulletToSpawn->GetCollider()->SetDirection(glm::rotate(glm::vec3(0, bulletToSpawn->GetSpeed(), 0), glm::radians(bulletToSpawn->GetRotation()), glm::vec3(0, 0, 1)));
      bullets_.push_back(bulletToSpawn);
    }
  }
  
  void Shooter::ReduceCooldown(float amount)
  {
    cooldown_ -= amount;
    if (cooldown_ < 0)
      cooldown_ = 0;
  }
}