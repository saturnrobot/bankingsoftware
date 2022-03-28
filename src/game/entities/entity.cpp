#include "entity.h"

namespace game
{
    Entity::Entity(const glm::vec3 &position, GLuint texture, GLint num_elements, Collider *colldier, EffectObject *collision_effect, float speed, float shield, bool hidden)
        : GameObject(position, texture, num_elements, hidden)
    {
        collider_ = colldier;
        speed_ = speed;
        collision_effect_ = collision_effect;
        shield_ = shield;
        mass_ = 10;
    }

    Entity::Entity(const Entity &entity) : GameObject(entity)
    {
        collider_ = entity.collider_->clone();
        collision_effect_ = new EffectObject(*entity.collision_effect_);
        speed_ = entity.speed_;
        shield_ = entity.shield_;
        mass_ = entity.mass_;
    }

    Entity::~Entity()
    {
        delete collider_;
        delete collision_effect_;
    }

    void Entity::Update(float delta_time)
    {
        if (!collision_effect_->Paused())
        {
            collision_effect_->Update(delta_time);
        }
    }

    void Entity::Render(Shader &shader)
    {
        if (!collision_effect_->IsHidden())
        {
            collision_effect_->Render(shader);
        }
        GameObject::Render(shader);
    }

    bool Entity::CheckCollisionEntity(Entity *collider)
    {
        if (!CanCollide(collider->GetCollider()) || !collider->CanCollide(GetCollider()))
        {
            return false;
        }
        if(collider->GetCollider()->GetTag() == "buoy") {
            return false;
        }
        if (collider_->CheckCollision(collider->GetCollider()))
        {
            if (shield_ > 0)
            {
                --shield_;
                return false;
            }
            Collision(collider);
            return true;
        }
        return false;
    }

    void Entity::ReduceShield(int amount)
    {
        if (shield_ == 0)
            return;
        shield_ -= amount;
        if (shield_ < 0)
            shield_ = 0;
    }

    void Entity::Collision(Entity *collider)
    {
        std::vector<GameObject *> gameObjectsToEffect;
        gameObjectsToEffect.push_back(this);
        collision_effect_->Activate(midpoint(position_, collider->GetPosition()), gameObjectsToEffect);
    }
}