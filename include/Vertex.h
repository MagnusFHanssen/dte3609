#pragma once

#include "../../glm-master/glm/glm.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
    glm::vec2 TexCoord2;
};

/*namespace Helper{

void setNormals(Vertex &a, Vertex &b, Vertex &c){
    glm::vec3 u = c.Position - b.Position;
    glm::vec3 v = a.Position - b.Position;

    glm::vec3 normal = glm::cross(u, v);

    normal = glm::normalize(normal);

    a.Normal = normal;
    b.Normal = normal;
    c.Normal = normal;
}
}*/
