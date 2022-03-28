#ifndef CIRCLE_COLLIDER_H_
#define CIRCLE_COLLIDER_H_

#include "../collider.h"
#include <glm/glm.hpp>

namespace game
{
    class CircleCollider : public Collider
    {
        public:
            CircleCollider(const std::string& tag, float radius=0.3);
            virtual bool CheckCollision(Collider *collider) const override;
            virtual bool CheckCollision(CircleCollider *collider) const;
            inline float GetRadius(void) const { return radius_; }

            inline virtual CircleCollider* clone(void) override { return new CircleCollider(*this); }
            inline virtual CircleCollider* visit(void) override { return this; }
            
          protected:
            float radius_;
    };
}

#endif // CIRCLE_COLLIDER_H_