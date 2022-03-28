#include "game_object.h"

namespace game
{

    GameObject::GameObject(const glm::vec3 &position, GLuint texture, GLint num_elements, bool hidden)
    {
        // Initialize all attributes
        this->position_ = position;
        this->scale_ = 1.0;
        this->velocity_ = glm::vec3(0.0f, 0.0f, 0.0f); // Starts out stationary
        this->num_elements_ = num_elements;
        this->texture_ = texture;
        this->hidden_ = hidden;
        this->rotation_ = 0;
    }

    GameObject::~GameObject() {}

    void GameObject::Update(float delta_time) {}

    void GameObject::SetRotation(float rotation)
    {
        rotation_ = (fmod(fmod(rotation, 360) + 360, 360));
    }

    void GameObject::Render(Shader &shader)
    {
        // Do not render if hidden is set
        if (hidden_)
            return;
        GameObject::RenderWithMatrix(shader, GameObject::GetRenderMatrix());
    }

    glm::mat4 GameObject::GetRenderMatrix()
    {
        glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, 1));
        glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);
        glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation_), glm::vec3(0, 0, 1));
        return scaling_matrix * translation_matrix * rotation_matrix;
    }

    void GameObject::RenderWithMatrix(Shader &shader, glm::mat4 transformation_matrix)
    {
        glBindTexture(GL_TEXTURE_2D, texture_);
        shader.SetUniformMat4("transformation_matrix", transformation_matrix);

        if (delete_)
        {
            shader.SetUniform1f("deceased", 1);
        }
        else
        {
            shader.SetUniform1f("deceased", 0);
        }

        // Draw the entity
        glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);
    }

} // namespace game
