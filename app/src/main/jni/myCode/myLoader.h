//
// Created by javan on 2/28/2018.
//

#ifndef DEMOOBJ_MYLOADER_H
#define DEMOOBJ_MYLOADER_H

#include <map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../common/myGLM.h"
#include "../common/myGLFunctions.h"

class MyLoader {
// info used to render a mesh
    struct Mesh {
        aiMesh *mesh;

        GLuint numVerts;
        GLuint numTextures;
        GLuint numNormals;
        GLuint numFaces;
        GLuint numVertsRefrence;
        GLuint normalsBuffer;
        GLuint vertsBuffer;
        GLuint textureCoordBuffer;
    };
public:
    MyLoader();

    ~MyLoader();

    void Render3dModel(glm::mat4 *MVP);

    void Load3dModel(std::string modelFilename);

    void Delete3DModel();

private:

    int loadShader(unsigned type, std::string shaderCode);

    int createAndLinkProgram(unsigned int vShader, unsigned int fShader, std::string *attributes);

    void GenerateGlBuffer();

    bool LoadTextuerToGL(std::string ModelFileName);

    std::vector<struct Mesh> modelMeshes;
    std::vector<GLfloat> vertex;       // contains one struct for every mesh in model
    std::vector<GLuint> indices;       // contains one struct for every mesh in model


    Assimp::Importer *importerPtr;
    const aiScene *scene;                           // assimp's output data structure
    bool isObjectLoaded;

    std::map<std::string, GLuint> textureNameMap;   // (texture filename, texture name in GL)

    GLuint vertexAttribute, vertexUVAttribute;     // attributes for shader variables
    int shaderProgramID;
    GLint mvpLocation, textureSamplerLocation;    // location of MVP in the shader


};


#endif //DEMOOBJ_MYLOADER_H
