#ifndef COLLIDER_H_
#define COLLIDER_H_

#include "effect_object.h"
#include "game_object.h"
#include <glm/vec3.hpp>
#include <string>

namespace game
{
    class Collider
    {
        public:
          Collider(const std::string& tag, const glm::vec3 *position = nullptr);
          virtual ~Collider();
          inline const glm::vec3 *GetPosition(void) const { return position_; }
          inline void Init(const glm::vec3 *position) { position_ = position; }
          inline const std::string& GetTag() const { return tag_; }
          virtual bool CheckCollision(Collider *collider) const = 0;
          virtual Collider *clone(void) = 0;
          virtual Collider *visit(void) = 0;
            
        protected:
            const glm::vec3 *position_;
            const std::string tag_;
    };
}

#endif // COLLIDER_H_