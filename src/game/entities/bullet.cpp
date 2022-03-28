#include "bullet.h"
#include "entity.h"

namespace game
{
    Bullet::Bullet(const glm::vec3 &position, GLuint texture, GLint num_elements, RayCollider *collider, EffectObject *collision_effect, float speed, float alive_time, bool hidden)
        : Entity(position, texture, num_elements, collider, collision_effect, speed, hidden)
    {
        spawn_time_ = 0;
        alive_time_ = alive_time;
    }

    Bullet::Bullet(const Bullet &bullet) : Entity(bullet)
    {
        collider_ = bullet.collider_->clone();
        alive_time_ = bullet.alive_time_;
        spawn_time_ = 0;
    }

    void Bullet::Update(float delta_time)
    {
        Entity::Update(delta_time);
        if (paused_)
        {
            return;
        }
        position_ += glm::rotate(glm::vec3(0, speed_, 0), glm::radians(GameObject::GetRotation()), glm::vec3(0, 0, 1)) * delta_time;

        spawn_time_ += delta_time;
        if (spawn_time_ > alive_time_)
        {
            delete_ = true;
        }
    }

    void Bullet::Collision(Entity *collider)
    {
        std::vector<GameObject *> gameObjectsToEffect;
        gameObjectsToEffect.push_back(collider);
        collision_effect_->Activate(collider->GetPosition(), gameObjectsToEffect);
        alive_time_ = collision_effect_->GetAliveTime() + 1;
    }
}