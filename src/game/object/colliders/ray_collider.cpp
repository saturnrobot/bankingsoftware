#include "ray_collider.h"

namespace game
{
    RayCollider::RayCollider(const std::string &tag, const glm::vec3 &direction) : Collider(tag), direction_(direction)
    {
    }

    bool RayCollider::CheckCollision(Collider *collider) const
    {
        return RayCollider::CheckCollision(static_cast<CircleCollider *>(collider));
    }

    bool RayCollider::CheckCollision(CircleCollider *collider) const
    {
        glm::vec2 dNorm = glm::normalize(glm::vec2(direction_.x, direction_.y));
        glm::vec2 diff = glm::vec2(position_->x, position_->y) - glm::vec2(collider->GetPosition()->x, collider->GetPosition()->y);
        float a = glm::dot(dNorm, dNorm);
        float b = glm::dot(2.0f * dNorm, diff);
        float c = glm::dot(diff, diff) - collider->GetRadius() * collider->GetRadius();
        float ds = glm::sqrt(b * b - 4.0f * a * c);
        float t1 = (-b - ds) / (2 * a);
        float t2 = (-b + ds) / (2 * a);
        return (t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1);
    }

}