#include "orbiter.h"
namespace game
{
    Orbiter::Orbiter(const glm::vec3 &position, GLuint texture, GLint num_elements, float radius, float speed, glm::vec3 center, float start_angle, const glm::vec3 &offset, bool hidden)
        : FollowerObject(position, texture, num_elements, offset, hidden), center_(center)
    {
        position_ = position + offset;
        radius_ = radius;
        speed_ = speed;
        t_ = 0;
        scale_ = 0.2;
        angle_ = start_angle;
    }
    
    void Orbiter::Update(float delta_time)
    {
        t_ = fmod((t_ + delta_time), 360.0);
        float a = fmod(angle_ + t_ * speed_, 360.0);
        position_ = glm::vec3(center_.x + cos(a) * radius_, center_.y + sin(a) * radius_, position_.z);
    }
}