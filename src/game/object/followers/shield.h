#ifndef SHIELD_H
#define SHIELD_H

#include "../follower_object.h"
#include "orbiter.h"
#include "../../entities/entity.h"

namespace game
{
    class Shield : public FollowerObject
    {
        public:
            Shield(const glm::vec3 &position, GLuint texture, GLint num_elements, Entity *parent, Orbiter *orbiter, const glm::vec3 &offset = glm::vec3(0.0f), bool hidden = false);
            ~Shield();
            virtual void Update(float delta_time) override;
            virtual void RenderWithMatrix(Shader &shader, glm::mat4 transformation_matrix) override;
        private:
            Entity* parent_;
            int current_shield_count_;
            std::vector<Orbiter *> orbiters_;
            Orbiter *base_orbiter_;
    };
}
#endif // SHIELD_H