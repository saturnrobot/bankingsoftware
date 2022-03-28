#ifndef PARENT_ENTITY_H_
#define PARENT_ENTITY_H_

#include "../game_object.h"
#include "vector"

namespace game {
class ParentEntity {

public:
  ParentEntity(const std::vector<GameObject *> &children = {});
  ~ParentEntity();
  virtual void UpdateChildren(float delta_time);
  virtual void RenderChildren(Shader &shader, GameObject *parent);
  void AddChild(GameObject* child);
private:
  std::vector<GameObject *> children_;
};

} // namespace game

#endif // PARENT_ENTITY_H_