#ifndef ADDSHIELD_H
#define ADDSHIELD_H

#include "../collectible.h"
#include "../../object/followers/orbiter.h"
namespace game
{
    class AddShield : public Collectible
    {
        public:
            AddShield(const glm::vec3 &position, GLuint texture, GLint num_elements, CircleCollider *collider, EffectObject *collision_effect);
            virtual void Effect(PlayerEntity *player) override;
    };
}

#endif // ADDSHIELD_H