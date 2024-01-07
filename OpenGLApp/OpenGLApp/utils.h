#ifndef __UTILS_H
#define __UTILS_H

#include <glm/glm.hpp>

#define XaxisVersor glm::vec2(1, 0)
#define YaxisVersor glm::vec2(0, -1)

float angleBetween(glm::vec2 a, glm::vec2 b, glm::vec2 origin);

glm::vec2 mouse2graphicCoords(glm::vec2 mouseCoords, glm::vec2 screenSize);

#endif
