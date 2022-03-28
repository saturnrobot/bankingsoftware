#ifndef ENTITY_H_
#define ENTITY_H_

#include "../object/game_object.h"
#include "../object/colliders/circle_collider.h"
#include "../utilities/util.h"

namespace game {
    class Entity : public GameObject
    {
        public:
            Entity(const glm::vec3 &position, GLuint texture, GLint num_elements, Collider *collider, EffectObject *collision_effect, float speed = 0, float shield = 0, bool hidden=false);
            Entity(const Entity &entity);
            ~Entity();
            inline float GetSpeed(void) { return speed_; }
            inline virtual Collider* GetCollider(){ return collider_->visit(); }
            inline virtual void Init() override { collider_->Init(&position_); }
            virtual void Update(float delta_time) override;
            virtual void Render(Shader &shader) override;
            virtual bool CheckCollisionEntity(Entity *collider);
            inline int GetShield() const { return shield_; }
            inline float GetMass() const { return mass_; }
            void ReduceShield(int amount = 1);
            void AddShield(int amount = 1) { shield_ += amount; }
            inline bool NoShield() const { return shield_ == 0;}
            inline virtual bool CanCollide(Collider *col) { return !paused_ && !hidden_ && col->GetTag() != "collectible"; }

        protected:
            virtual void Collision(Entity *collider);
            float speed_;
            int shield_;
            EffectObject *collision_effect_;
            Collider *collider_;
            float mass_;
    };
}
#endif // ENTITY_H_