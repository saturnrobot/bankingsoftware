#include "effect_object.h"
#include "game_object.h"
#include <iostream>

namespace game
{
    EffectObject::EffectObject(const glm::vec3 &position, GLuint texture, GLint num_elements, double alive_time, bool hidden, int sound_index)
        : GameObject(position, texture, num_elements, hidden)
    {
        alive_time_ = alive_time;
        paused_ = true;
        spawn_time_ = 0;
        sound_index_ = sound_index;
    }
    
    EffectObject::EffectObject(const EffectObject &effect) : GameObject(effect)
    {
        alive_time_ = effect.alive_time_;
        sound_index_ = effect.sound_index_;
        spawn_time_ = 0;
        paused_ = true;
        hidden_ = true;
    }

    void EffectObject::Update(float delta_time)
    {
        if (paused_)
            return;

        spawn_time_ += delta_time;

        if (spawn_time_ > alive_time_)
        {
            Deactivate();
        }
    }

    void EffectObject::Render(Shader &shader)
    {
        // Do not render if hidden is set
        if (hidden_)
            return;
        
        // Bind the entity's texture
        glBindTexture(GL_TEXTURE_2D, texture_);

        // Setup the scaling matrix for the shader
        glm::mat4 scaling_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, scale_, -2));

        // Set up the translation matrix for the shader
        glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position_);

        glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation_), glm::vec3(0, 0, 1));

        // Setup the transformation matrix for the shader
        glm::mat4 transformation_matrix = scaling_matrix * translation_matrix * rotation_matrix;

        // TODO: Add other types of transformations

        // Set the transformation matrix in the shader
        shader.SetUniformMat4("transformation_matrix", transformation_matrix);
        // Draw the entity
        glDrawElements(GL_TRIANGLES, num_elements_, GL_UNSIGNED_INT, 0);
    }

    void EffectObject::Activate(const glm::vec3 &position, std::vector<GameObject *> effectors)
    {
        effectors_ = effectors;
        position_ = glm::vec3(position.x, position.y, 1);
        hidden_ = false;
        paused_ = false;
        for (GameObject *obj : effectors_)
        {
            obj->Pause(true);
        }
    }

    void EffectObject::Activate(const glm::vec3 &position, std::vector<GameObject *> effectors, audio_manager::AudioManager *am)
    {
      Activate(position, effectors);
      if (sound_index_ > -1) {
        am->SetSoundPosition(sound_index_, position.x, position.y, position.z);
        am->PlaySound(sound_index_);
        }
    }

    void EffectObject::Deactivate()
    {
        for (GameObject *obj : effectors_)
        {
            obj->MarkForDeletion();
        }
        hidden_ = true;
        paused_ = true;
        spawn_time_ = 0;
        effectors_.clear();
        // MarkForDeletion();
    }
} // namespace game