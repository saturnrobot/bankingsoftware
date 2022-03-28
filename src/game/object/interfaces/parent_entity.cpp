#include "parent_entity.h"

namespace game
{
    ParentEntity::ParentEntity(const std::vector<GameObject *> &children)
    {
        this->children_ = children;
    }

    ParentEntity::~ParentEntity()
    {
        for (GameObject *child : children_)
        {
            delete child;
        }
    }

    void ParentEntity::UpdateChildren(float delta_time)
    {
        for (std::vector<GameObject *>::iterator child = children_.begin(); child != children_.end();)
        {
            (*child)->Update(delta_time);
            if ((*child)->MarkedForDeletion()) {
                children_.erase(child);
            } else {
                ++child;
            }
        }
    }

    void ParentEntity::RenderChildren(Shader &shader, GameObject* parent)
    {
        for (GameObject *child : children_)
        {
            if (child->IsHidden())
                return;
            glm::mat4 transformation_matrix = parent->GetRenderMatrix() * child->GetRenderMatrix();
            child->RenderWithMatrix(shader, transformation_matrix);
        }
    }

    void ParentEntity::AddChild(GameObject *child)
    {
        children_.push_back(child);
    }
}