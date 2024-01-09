#ifndef __UTILS_H
#define __UTILS_H

#include <glm/glm.hpp>

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

#define XaxisVersor glm::vec2(1, 0)
#define YaxisVersor glm::vec2(0, -1)

#define root2div2 (float) 0.70710678

float angleBetween(glm::vec2 a, glm::vec2 b, glm::vec2 origin);

// uses (0,0) as origin
float angleBetweenVerticalDir(glm::vec2 a);

glm::vec2 mouse2graphicCoords(glm::vec2 mouseCoords, glm::vec2 screenSize);

glm::vec2 scaleVector(glm::vec2 vector);

#endif
