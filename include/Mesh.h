#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

class Mesh
{
    public:
        Mesh();
        Mesh(std::vector<glm::vec3> vertices);
        void render();
    private:
        std::vector<glm::vec3> vertices;
        GLuint vboID;
};

#endif // MESH_H
