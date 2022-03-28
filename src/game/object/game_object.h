#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>

#include "../engine/shader/shader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace game
{

    /*
        GameObject is responsible for handling the rendering and updating of objects in the game world
        The update method is virtual, so you can inherit from GameObject and override the update functionality (see PlayerEntity for reference)
    */
    class GameObject
    {

    public:
        // Constructor
        GameObject(const glm::vec3 &position, GLuint texture, GLint num_elements, bool hidden = false);
        virtual ~GameObject();

        // Update the GameObject's state. Can be overriden for children
        virtual void Update(float delta_time);

        // Renders the GameObject using a shader
        virtual void Render(Shader &shader);

        inline virtual void Init() {};

        // Getters
        inline glm::vec3 &GetPosition(void) { return position_; }
        inline float GetScale(void) { return scale_; }
        inline glm::vec3 &GetVelocity(void) { return velocity_; }
        inline bool IsHidden(void) { return hidden_; }
        inline bool Paused(void) { return paused_; }
        inline bool MarkedForDeletion(void) { return delete_; }
        inline float GetRotation(void) { return rotation_; }
        
        glm::mat4 GetRenderMatrix();
        virtual void RenderWithMatrix(Shader &shader, glm::mat4 transformation_matrix);

        // Setters
        inline void SetPosition(const glm::vec3 &position) { position_ = position; }
        inline void SetScale(float scale) { scale_ = scale; }
        inline void SetHidden(bool hidden) { hidden_ = hidden; }
        inline void Pause(bool pause) { paused_ = pause; }
        inline void SetVelocity(const glm::vec3 &velocity) { velocity_ = velocity; }
        virtual inline void MarkForDeletion(void)
        {
            delete_ = true;
            hidden_ = false;
            paused_ = true;
        }
        void SetRotation(float rotation);

    protected:
        // Object's Transform Variables
        // TODO: Add more transformation variables
        glm::vec3 position_;
        float scale_;
        glm::vec3 velocity_;

        float rotation_;

        // Object's details
        GLint num_elements_;

        // Object's texture reference
        GLuint texture_;

        bool hidden_;
        bool paused_ = false;
        bool delete_ = false;

    }; // class GameObject

} // namespace game

#endif // GAME_OBJECT_H_
