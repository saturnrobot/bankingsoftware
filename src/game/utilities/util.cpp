#include "util.h"
glm::vec3 midpoint(glm::vec3 x1, glm::vec3 x2) { return glm::vec3((x1.x + x2.x) / 2, (x1.y + x2.y) / 2, (x1.z + x1.z) / 2); }

int randi(float min, float max)
{
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(min,max);
    return dist(rng);
}

float randf(float min, float max)
{
    random_device dev;
    mt19937 rng(dev());
    uniform_real_distribution<float> dist(min,max);
    return dist(rng);
}