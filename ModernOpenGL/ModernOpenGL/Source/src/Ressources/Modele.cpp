#include <iostream>
#include <fstream>
#include <string>
#include "Ressources/Model.h"

void Model::Load(const char* modelPath)
{
    std::ifstream file;
    file.open(modelPath);
    std::string line;
    std::vector<Vector3> positions;
    std::vector<Vector3> normals;
    std::vector<Vector2> textureUVs;

    while (!file.eof())
    {
        std::getline(file, line);
        if (line[0] == 'v' && line[1] == 't')
        {
            Vector2 vt;
            sscanf_s(line.c_str(), "%f %f", &vt.x, &vt.y);
            textureUVs.push_back(vt);
        }
        else if (line[0] == 'v' && line[1] == 'n')
        {
            Vector3 vn;
            sscanf_s(line.c_str(), "%f %f %f", &vn.x, &vn.y, &vn.z);
            normals.push_back(vn);
        }
        else if (line[0] == 'v')
        {
            Vector3 v;
            sscanf_s(line.c_str(), "%f %f %f", &v.x, &v.y, &v.z);
            positions.push_back(v);
        }
        else if (line[0] == 'f')
        {
            Vertex v1;
            Vertex v2;
            Vertex v3;
            Vector3 i1;
            Vector3 i2;
            Vector3 i3;
            sscanf_s(line.c_str(), "%d %d %d %d %d %d %d %d %d", &i1.x, &i1.y, &i1.z, &i2.x, &i2.y, &i2.z, &i3.x, &i3.y, &i3.z);
            v1.Position = positions[i1.x];
            v1.TextureUV = textureUVs[i1.y];
            v1.Normal = normals[i1.z];
            v2.Position = positions[i2.x];
            v2.TextureUV = textureUVs[i2.y];
            v2.Normal = normals[i2.z];
            v3.Position = positions[i3.x];
            v3.TextureUV = textureUVs[i3.y];
            v3.Normal = normals[i3.z];
        }
    }

    
}