#include "buoy.h"
namespace game {
    Buoy::Buoy(const glm::vec3 &position, GLuint texture, GLint num_elements, Collider *collider, EffectObject *collision_effect, float mass)
        : Entity(position, texture, num_elements, collider, collision_effect)
    {
        mass_ = mass;
    }
    
    void Buoy::Update(float delta_time)
    {
        position_ += velocity_ * delta_time;
    }
    
    void Buoy::Collision(Entity *collider)
    {
        glm::vec3 n = glm::normalize(collider->GetPosition() - position_);
        std::cout << collider->GetVelocity().x << " " << collider->GetVelocity().y << std::endl;
        glm::vec3 v = collider->GetVelocity();
        if (collider->GetCollider()->GetTag() == "player") {
            v *= 25.0f;
        }
        velocity_ = (velocity_ - ((2*collider->GetMass())/(mass_ + collider->GetMass())) * (glm::dot(n, velocity_ - v)) * n);
        collider->SetVelocity((v - ((2*mass_)/(mass_ + collider->GetMass())) * (glm::dot(n, v - velocity_)) * n));
    }
    
}