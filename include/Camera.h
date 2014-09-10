#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
    public:
        Camera(float fov, float x, float y, float z, int SCREEN_WIDTH, int SCREEN_HEIGHT);
        glm::vec3 position;
        float fieldOfView;
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        float camAngle = 0;
};

#endif // CAMERA_H
