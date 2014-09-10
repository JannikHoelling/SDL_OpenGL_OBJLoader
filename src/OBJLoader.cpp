#include "OBJLoader.h"


Mesh loadOBJ() {
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    std::ifstream file("untitled.obj");
    std::string line;

    //Loop through each line
    while(std::getline(file, line))
    {
        std::stringstream linestream(line);
        char pre;
        //float val1;
       // float val2;
        //float val3;

        // Read the values into the variables using the operator >>
        linestream >> pre;
        //>> val1 >> val2 >> val3;
        /*if(pre != '#') {
            linestream >> val1 >> val2;
            std::cout << val1 << "|" << val2 << "|" << val3 << std::endl;

        }*/

        //Switch to determine what kind of data that line has
        switch(pre) {
            case '#': break; //Comment
            case 'o': break; //Object name
            case 'v':
                float v1, v2, v3;
                linestream >> v1 >> v2 >> v3;
                vertices.push_back(glm::vec3(v1, v2, v3)); break; //Vertex
            case 'f':
                unsigned int f1, f2, f3;
                linestream >> f1 >> f2 >> f3;
                indices.push_back(f1-1); indices.push_back(f2-1); indices.push_back(f3-1); break; //Face
        }
    }

    return Mesh(vertices, indices);
}
