#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>

#include <tiny_obj_loader.h>

class Mesh
{
    public:
        Mesh();
        Mesh(std::vector<float> vertices, std::vector<float> uvs, std::vector<unsigned int> indices);
        void render(GLuint shaderProgram);
    private:
        //std::vector<glm::vec3> vertices;
        //std::vector<glm::vec2> uvs;
        std::vector<float> vertices;
        std::vector<float> uvs;
        std::vector<unsigned int> indices;
        GLuint vboID;
        GLuint uvID;
        GLuint indexID;
        GLuint texture;
};

Mesh loadOBJ();

#endif // MESH_H
