/*
 *    Copyright 2016 Anand Muralidhar
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef ASSIMPLOADER_H
#define ASSIMPLOADER_H

#include <map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "myGLM.h"
#include "myGLFunctions.h"
#include "../myCode/myMesh.h"

// info used to render a mesh

class AssimpLoader {

public:
    AssimpLoader();

    ~AssimpLoader();

    void Render3DModel(glm::mat4 *MVP);
    void Render3DModelnew(unsigned i);

    bool Load3DModel(std::string modelFilename);

    void Delete3DModel();

    void MyLoad3DModel(MyMesh *mesh, glm::mat4 *mvpMat);

private:
    void GenerateGLBuffers();

    bool LoadTexturesToGL(std::string modelFilename);

    std::vector<struct MeshInfo> modelMeshes;       // contains one struct for every mesh in model
    std::vector<GLfloat> vertex;       // contains one struct for every mesh in model
    std::vector<GLuint> indices;       // contains one struct for every mesh in model

    Assimp::Importer *importerPtr;
    const aiScene *scene;                           // assimp's output data structure
    bool isObjectLoaded;

    std::map<std::string, GLushort > textureNameMap;   // (texture filename, texture name in GL)

    GLuint vertexAttribute, vertexUVAttribute;     // attributes for shader variables
    GLuint shaderProgramID;
    GLuint *vertexShaderID ;
    GLuint *fragmentShaderID;
    GLint mvpLocation, textureSamplerLocation;    // location of MVP in the shader

    GLint uniform_m,uniform_v,uniform_p,uniform_m_3x3_inv_transp,uniform_v_inv;
    GLuint attribute_v_coord,attribute_v_normal;
};
struct MeshInfo {
    aiMesh *mesh;
    GLushort textureIndex;
    int numberOfFaces;
    int numberOfVertice;
    GLuint faceBuffer;
    GLuint vertexBuffer;
    GLuint textureCoordBuffer;
};

#endif //ASSIMPLOADER_H