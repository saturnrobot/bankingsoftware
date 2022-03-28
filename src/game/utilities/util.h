#ifndef __UTIL_H__
#define __UTIL_H__

#include <glm/glm.hpp>
#include <random>
using namespace std;

glm::vec3 midpoint(glm::vec3 x1, glm::vec3 x2);
int randi(float min, float max);
float randf(float min = 0, float max = 1);
#endif // __UTIL_H__