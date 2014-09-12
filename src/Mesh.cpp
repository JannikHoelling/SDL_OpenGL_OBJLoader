#include "Mesh.h"

#include "textureLoader.h"

Mesh::Mesh() {

}

Mesh::Mesh(std::vector<float> vertices, std::vector<float> uvs, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->uvs = uvs;
    this->indices = indices;
    glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &uvID);
	glBindBuffer(GL_ARRAY_BUFFER, uvID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->uvs.size(), uvs.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &indexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    texture = loadTexture("bunny.bmp");
}

void Mesh::render(GLuint shaderProgram) {
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glCullFace(GL_BACK);

    glBindTexture( GL_TEXTURE_2D, texture );
    GLint textureLocation = glGetUniformLocation(shaderProgram, "texture");
    glUniform1i(textureLocation, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)sizeof(glm::vec4));
    glBindBuffer(GL_ARRAY_BUFFER, uvID);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
    glDrawElements(GL_TRIANGLES,indices.size(), GL_UNSIGNED_INT, 0);

    //glDrawArrays(GL_POINTS, 0, vertices.size());

}

Mesh loadOBJ() {
    tinyobj::mesh_t mesh;
    std::vector<tinyobj::shape_t> shapes;

    std::string err = tinyobj::LoadObj(shapes, "bunny.obj");

    if (!err.empty()) {
        std::cerr << err << std::endl;
    }
    mesh = shapes[0].mesh;

    std::cout << "Loaded model with : " << mesh.positions.size()/3 << " vertices." << std::endl;

    //return Mesh(vertices, uvs, indices);
    return Mesh(mesh.positions, mesh.texcoords, mesh.indices);
}


