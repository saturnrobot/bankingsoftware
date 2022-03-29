#include "player_entity.h"

namespace game
{
	const float PlayerEntity::drag_coeff_ = 0.3f;
	PlayerEntity::PlayerEntity(const glm::vec3 &position, GLuint texture, GLint num_elements, CircleCollider *collider, EffectObject *collision_effect, float speed, int shield, Bullet *bullet, float cooldown, const std::vector<GameObject *> &children, bool hidden)
		: Entity(position, texture, num_elements, collider, collision_effect, speed, shield, hidden), ParentEntity(children), Shooter(bullet, cooldown)
	{
		acceleration_ = glm::vec3(0);
	}
	// Update function for moving the player object around
	void PlayerEntity::Update(float delta_time)
	{
		Entity::Update(delta_time);
		if (paused_)
			return;

		//GameObject::Update(delta_time);
		glm::vec3 currentVelocity = GameObject::GetVelocity();

		if(glm::length(currentVelocity) > max_velocity_) {
			acceleration_ -= (glm::normalize(currentVelocity) * (glm::length(currentVelocity)*glm::length(currentVelocity)) * 5.0f);
		}

		velocity_ = 0.5f * (acceleration_ * delta_time);
		glm::vec3 drag = -drag_coeff_ * glm::normalize(velocity_);

		if(glm::length(velocity_) < 0.01f) {
			velocity_ = glm::vec3(0);
		} else if(glm::length(velocity_) > glm::length(drag)) {
			velocity_ += drag;
		}

		position_ += velocity_;

		ParentEntity::UpdateChildren(delta_time);
		Shooter::UpdateShots(delta_time);
	}
	
	void PlayerEntity::Render(Shader &shader)
	{
		Entity::Render(shader);
		if(hidden_)
			return;
		ParentEntity::RenderChildren(shader, this);
		Shooter::RenderShots(shader);
    }

	void PlayerEntity::RotateLeft()
	{
		GameObject::SetRotation(GameObject::GetRotation() - rot_speed_);
	}

	void PlayerEntity::RotateRight()
	{
		GameObject::SetRotation(GameObject::GetRotation() + rot_speed_);
	}

	void PlayerEntity::MoveForward()
	{
		acceleration_ += glm::rotate(glm::vec3(0, speed_, 0), glm::radians(GameObject::GetRotation()), glm::vec3(0,0,1));
	}

	void PlayerEntity::MoveBackward()
	{
		acceleration_ += glm::rotate(glm::vec3(0, -speed_, 0), glm::radians(GameObject::GetRotation()), glm::vec3(0,0,1));
	}
	
	void PlayerEntity::LookAtPoint(glm::vec2 target)
	{
		float angle = glm::degrees(glm::atan(target.y - position_.y, target.x - position_.x));
		if (angle < 0) {
			angle = 360 - (-angle);
		}
		GameObject::SetRotation(angle - 90);
	}
	
	void PlayerEntity::Stop()
	{
		acceleration_ *= 0.99;
	}
	
	void PlayerEntity::MarkForDeletion()
	{
		delete_ = true;
		Shooter::DeleteShots();
	}
}
