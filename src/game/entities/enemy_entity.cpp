#include "enemy_entity.h"
#include "entity.h"

namespace game
{

    /*
    PlayerEntity inherits from GameObject
    It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

    EnemyEntity::EnemyEntity(const glm::vec3 &position, GLuint texture, GLint num_elements, float seeRadius, CircleCollider *collider, EffectObject *collision_effect, float speed, bool hidden)
        : Entity(position, texture, num_elements, collider, collision_effect, speed, hidden)
    {
        seeRadius_ = seeRadius;
        state_ = patrolling;
        timecounter_ = 0;
    }

    // Update function for moving the player object around
    void EnemyEntity::Update(float delta_time)
    {
        Entity::Update(delta_time);
        if (paused_)
            return;
        if (state_ == moving)
        {
            EnemyEntity::Move(delta_time);
        }
        else
        {
            EnemyEntity::Patrol(delta_time);
        }
    }

    void EnemyEntity::Move(float delta_time)
    {
        if (paused_)
        {
            return;
        }

        glm::vec3 towards = position_ - target_;
        velocity_ += glm::normalize(towards) * -speed_ * (float)delta_time;
        float distance = glm::length(position_ - target_);
        if (distance > seeRadius_ + 1)
        {
            velocity_ = glm::vec3(0, 0, velocity_.z);
            state_ = patrolling;
        }
        position_ += velocity_ * delta_time;
    }

    void EnemyEntity::Patrol(float delta_time)
    {
        timecounter_ = fmod((timecounter_ + delta_time), 360.0);
        position_ = glm::vec3(position_.x + cos(timecounter_ * 1.1) * 0.02, position_.y + sin(timecounter_ * 1.1) * 0.02, position_.z);
    }
}