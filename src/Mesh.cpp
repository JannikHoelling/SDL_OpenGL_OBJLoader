#include "Mesh.h"

Mesh::Mesh() {

}

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;
    glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &indexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void Mesh::render() {
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)sizeof(glm::vec4));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
    glDrawElements(GL_TRIANGLES,indices.size(), GL_UNSIGNED_INT, 0);

    //glDrawArrays(GL_POINTS, 0, vertices.size());

}
