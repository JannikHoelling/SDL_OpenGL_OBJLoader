#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

class Mesh
{
    public:
        Mesh();
        Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
        void render();
    private:
        std::vector<glm::vec3> vertices;
        std::vector<unsigned int> indices;
        GLuint vboID;
        GLuint indexID;
};

#endif // MESH_H
