#include "shield.h"
namespace game
{
    Shield::Shield(const glm::vec3 &position, GLuint texture, GLint num_elements, Entity *parent, Orbiter *orbiter, const glm::vec3 &offset, bool hidden)
        : FollowerObject(position, texture, num_elements, offset, hidden)
    {
        parent_ = parent;
        float angle = 360 / parent->GetShield();
        for (int i = 0; i < parent->GetShield(); ++i)
        {
            Orbiter *orb = new Orbiter(*orbiter);
            orb->SetAngle(angle*i);
            orbiters_.push_back(orb);
        }
        current_shield_count_ = parent->GetShield();
        base_orbiter_ = orbiter;
    }

    Shield::~Shield()
    {
        for (std::vector<Orbiter *>::iterator orb = orbiters_.begin(); orb != orbiters_.end();)
        {
            orbiters_.erase(orb);
        }
        delete base_orbiter_;
    }

    void Shield::Update(float delta_time)
    {
        if (current_shield_count_ > parent_->GetShield())
        {
            std::cout << parent_->GetShield() << std::endl;
            while(current_shield_count_ > parent_->GetShield()) {
                orbiters_.pop_back();
                --current_shield_count_;
            }
        }
        else if (current_shield_count_ < parent_->GetShield())
        {
            while(current_shield_count_ < parent_->GetShield()) {
                orbiters_.push_back(new Orbiter(*base_orbiter_));
                ++current_shield_count_;
            }
        }
        for (Orbiter *orb : orbiters_)
        {
            orb->Update(delta_time);
        }
    }
    
    void Shield::RenderWithMatrix(Shader &shader, glm::mat4 transformation_matrix)
    {
        for (Orbiter *orb : orbiters_)
        {
            orb->RenderWithMatrix(shader, transformation_matrix * orb->GetRenderMatrix());
        }
    }
}