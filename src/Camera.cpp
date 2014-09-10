#include "Camera.h"

#define PI 3.14159265f

Camera::Camera(float fov, float x, float y, float z, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    this->position = glm::vec3(x, y, z);
    this->fieldOfView = fov;

    projectionMatrix = glm::perspective(fov * (PI/180), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.f);
	viewMatrix = glm::translate(viewMatrix, this->position);
	viewMatrix = glm::lookAt(this->position, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
