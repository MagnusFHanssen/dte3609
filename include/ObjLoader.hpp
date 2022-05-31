#pragma once

#include <gl/glew.h>
#include "../../glm-master/glm/gtc/matrix_transform.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace OBJLoader
{
    inline void mergeVertexAttributes(std::vector<float>& vertices, std::vector<float> const& pos, std::vector<float> const& normals, int const pOffset, int const nOffset)
    {
        int const noVertices = pos.size() / pOffset;
        int p = 0, n = 0;

        for (int i = 0; i < noVertices; i++)
        {
            vertices.push_back(pos.at(p));
            vertices.push_back(pos.at(p + 1));
            vertices.push_back(pos.at(p + 2));

            vertices.push_back(normals.at(n));
            vertices.push_back(normals.at(n + 1));
            vertices.push_back(normals.at(n + 2));

            p += pOffset;
            n += nOffset;
        }
    }

    inline void createIndices(std::vector<unsigned int>& indices, std::vector<float>& vertices, int const totOffset)
    {
        unsigned int const noIndices = vertices.size() / totOffset;

        for (unsigned int i = 0; i < noIndices; i++)
            indices.push_back(i);
    }

    // TODO not optimal because it doesn't reuse vertices, some are drawn on top of eachother
    inline void loadOBJ(const std::string& path, std::vector<unsigned int>& indices, std::vector<float>& vertices, int const pOffset, int const nOffset, int const totOffset)
    {
        std::vector<unsigned int> pIndices, nIndices;
        std::vector<glm::vec3> tempPos, tempN;
        std::vector<float> pos, n;

        std::ifstream stream(path);
        std::string line;

        if (not stream.good())
        {
            std::cout << "cannot open file object file" << std::endl;
            __debugbreak();
        }

        while (getline(stream, line))
        {
            if (line.substr(0, 2) == "v ")
            {
                float x, y, z;
                std::istringstream s(line.substr(2));
                s >> x >> y >> z;
                tempPos.push_back(glm::vec3(x, y, z));
            }
            else if (line.substr(0, 2) == "vn")
            {
                float x, y, z;
                std::istringstream s(line.substr(2));
                s >> x >> y >> z;
                tempN.push_back(glm::vec3(x, y, z));
            }
            else if (line.substr(0, 2) == "f ")
            {
                std::vector<std::string> indices;
                boost::split(indices, line, boost::is_any_of("/, "));

                for (int i = 1; i < indices.size(); i += 3)
                {
                    pIndices.push_back(boost::lexical_cast<unsigned int>(indices.at(i)));
                    nIndices.push_back(boost::lexical_cast<unsigned int>(indices.at(i + 2)));
                }
            }
        }

        for (unsigned int i = 0; i < pIndices.size(); i++)
        {
            unsigned int const index = pIndices[i] - 1;
            glm::vec3 const p = tempPos[index];
            pos.push_back(p.x);
            pos.push_back(p.y);
            pos.push_back(p.z);
        }

        for (unsigned int i = 0; i < nIndices.size(); i++)
        {
            unsigned int const index = nIndices[i] - 1;
            glm::vec3 const normal = tempN[index];
            n.push_back(normal.x);
            n.push_back(normal.y);
            n.push_back(normal.z);
        }

        mergeVertexAttributes(vertices, pos, n, pOffset, nOffset);
        createIndices(indices, vertices, totOffset);
    }
}
