#ifndef ORBITER_H
#define ORBITER_H

#include "../follower_object.h"

namespace game {
    class Orbiter : public FollowerObject {
        public:
            Orbiter(const glm::vec3 &position, GLuint texture, GLint num_elements, float radius, float speed, glm::vec3 center, float start_angle = 0, const glm::vec3 &offset = glm::vec3(0.0f), bool hidden = false);
            virtual void Update(float delta_time) override;
            inline void SetAngle(float angle) { angle_ = angle;}
        private:
            float radius_;
            float speed_;
            float t_;
            float angle_;
            glm::vec3 center_;
    };
}

#endif // ORBITER_H