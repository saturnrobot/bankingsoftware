#ifndef ENEMY_ENTITY_H_
#define ENEMY_ENTITY_H_

#include "entity.h"

namespace game
{
    class EnemyEntity : public Entity
    {
    public:
        EnemyEntity(const glm::vec3 &position, GLuint texture, GLint num_elements, float seeRadius, CircleCollider *collider, EffectObject *collision_effect, float speed, bool hidden = false);

        void Update(float delta_time) override;

        inline float GetSeeRadius(void) { return seeRadius_; }
        inline void SetTarget(glm::vec3 t) { target_ = t; }
        inline void SetChase() { state_ = moving; }
        inline virtual CircleCollider *GetCollider() override { return static_cast<CircleCollider *>(collider_); }

    protected:
        enum EnemyStates
        {
            patrolling,
            moving
        };
        EnemyStates state_;
        float seeRadius_;
        glm::vec3 target_;
        float timecounter_;

        void Patrol(float delta_time);
        void Move(float delta_time);
    };
} // namespace game
#endif // ENEMY_ENTITY_H_