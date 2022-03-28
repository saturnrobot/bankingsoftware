#include "collectible.h"
namespace game
{
    Collectible::Collectible(const glm::vec3 &position, GLuint texture, GLint num_elements, CircleCollider *collider, EffectObject *collision_effect)
        : Entity(position, texture, num_elements, collider, collision_effect)
    {
    }

    bool Collectible::CheckCollisionEntity(Entity *collider)
    {
        if (paused_ || hidden_ || collider->GetCollider()->GetTag() != "player")
        {
            return false;
        }
        if (collider_->CheckCollision(collider->GetCollider()))
        {
            Collision(collider);
            return true;
        }
        return false;
    }
}