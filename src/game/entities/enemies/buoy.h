#ifndef BUOY_H
#define BUOY_H

#include "../entity.h"

namespace game {
    class Buoy : public Entity {
        public:
            Buoy(const glm::vec3 &position, GLuint texture, GLint num_elements, Collider *collider, EffectObject *collision_effect, float mass);
            virtual void Update(float delta_time) override;
        protected:
            virtual void Collision(Entity *collider) override;
    };
}

#endif // BUOY_H