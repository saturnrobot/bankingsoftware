#ifndef EFFECT_OBJECT_H_
#define EFFECT_OBJECT_H_

#include "../engine/audio/audio_manager.h"
#include "game_object.h"
#include <vector>

namespace game {
class EffectObject : public GameObject {
  public:
    EffectObject(const glm::vec3 &position, GLuint texture, GLint num_elements, double alive_time, bool hidden, int sound_index = -1);
    EffectObject(const EffectObject &effect);
    void Update(float delta_time) override;
    void Render(Shader &shader) override;
    virtual void Activate(const glm::vec3 &position, std::vector<GameObject *> effectors);
    virtual void Activate(const glm::vec3 &position, std::vector<GameObject *> effectors, audio_manager::AudioManager *am);
    virtual void Deactivate();

    inline double GetAliveTime(void) { return alive_time_; }

  protected:
    double alive_time_;
    double spawn_time_;
    int sound_index_;
    std::vector<GameObject *> effectors_;
};
} // namespace game
#endif // EFFECT_OBJECT_H_