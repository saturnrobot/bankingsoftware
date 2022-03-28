#include "addshield.h"
namespace game
{
    AddShield::AddShield(const glm::vec3 &position, GLuint texture, GLint num_elements, CircleCollider *collider, EffectObject *collision_effect)
        : Collectible(position, texture, num_elements, collider, collision_effect_)
    {
        collision_effect_ = collision_effect;
    }
    
    void AddShield::Effect(PlayerEntity *player)
    {
        player->AddShield();
        delete_ = true;
    }
}