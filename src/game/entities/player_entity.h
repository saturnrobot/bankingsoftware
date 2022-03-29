#ifndef PLAYER_GAME_OBJECT_H_
#define PLAYER_GAME_OBJECT_H_

#include "entity.h"
#include "../object/interfaces/parent_entity.h"
#include "interfaces/shooter.h"
#include <glm/gtx/rotate_vector.hpp>

namespace game
{

  // Inherits from GameObject
  class PlayerEntity : public Entity, public ParentEntity, public Shooter
  {

  public:
    PlayerEntity(const glm::vec3 &position, GLuint texture, GLint num_elements, CircleCollider *collider, EffectObject *collision_effect, float speed, int shield, Bullet *bullet, float cooldown, const std::vector<GameObject *> &children = {}, bool hidden=false);

    // Update function for moving the player object around
    void Update(float delta_time) override;
    void Render(Shader &shader) override;

    void RotateLeft();
    void RotateRight();
    void MoveForward();
    void MoveBackward();
    void LookAtPoint(glm::vec2 target);
    void Stop();

    void MarkForDeletion() override;

    inline virtual CircleCollider *GetCollider() override { return static_cast<CircleCollider *>(collider_); }

  private:
    static const float drag_coeff_;
    float force_amount_ = 10;
    float rot_speed_ = 5;
    glm::vec3 acceleration_;
    float max_velocity_ = 0.0005;
    float max_force_ = 100;
    float min_force_ = -100;
    void GetInput(double delta_time);

  }; // class PlayerGameObject

} // namespace game

#endif // PLAYER_GAME_OBJECT_H_
