#include "Mesh.h"

Mesh::Mesh() {

}

Mesh::Mesh(std::vector<glm::vec3> vertices)
{
    this->vertices = vertices;
    glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->vertices.size(), vertices.data(), GL_STATIC_DRAW);
}

void Mesh::render() {
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)sizeof(glm::vec4));

    glDrawArrays(GL_POINTS, 0, vertices.size());

}
