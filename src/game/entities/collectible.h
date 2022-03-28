#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "entity.h"
#include "player_entity.h"
namespace game
{
    class Collectible : public Entity
    {
        public:
            Collectible(const glm::vec3 &position, GLuint texture, GLint num_elements, CircleCollider *collider, EffectObject *collision_effect);
            virtual void Effect(PlayerEntity *player) = 0;
            virtual bool CheckCollisionEntity(Entity *collider) override;
            inline virtual bool CanCollide(Collider *col) override { return !paused_ && !hidden_ && col->GetTag() == "player";}
        protected:
            inline virtual void Collision(Entity* collider) override { Effect(static_cast<PlayerEntity *>(collider)); }
    };
}

#endif // COLLECTIBLE_H