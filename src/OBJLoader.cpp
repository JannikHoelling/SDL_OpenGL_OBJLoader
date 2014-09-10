#include "OBJLoader.h"


Mesh loadOBJ() {
    std::vector<glm::vec3> vertices;

    std::ifstream file("dragon.obj");
    std::string line;

    while(std::getline(file, line))
    {
        std::stringstream linestream(line);
        char pre;
        float val1;
        float val2;
        float val3;

        // Read the values into the variables using the operator >>
        linestream >> pre >> val1 >> val2 >> val3;
        /*if(pre != '#') {
            linestream >> val1 >> val2;
            std::cout << val1 << "|" << val2 << "|" << val3 << std::endl;

        }*/

        switch(pre) {
            case '#': break; //Comment
            case 'o': break; //Object name
            case 'v': vertices.push_back(glm::vec3(val1, val2, val3)); break; //Vertex
        }
    }

    return Mesh(vertices);
}
