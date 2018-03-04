//
// Created by javan on 2/28/2018.
//

#include "myLoader.h"
#include "../common/myLogger.h"

MyLoader::MyLoader() {
    importerPtr = new Assimp::Importer();
    scene = NULL;
    isObjectLoaded = false;
    // shader related setup -- loading, attribute and uniform locations
    std::string vertexShader =
            "attribute  vec4 a_Position;\n"
                    "uniform  mat4 mvpMat;\n"
                    "void main(){\n"
                    "    gl_Position = mvpMat * a_Position;\n"
                    "    a_Position = 20.0;\n"
                    "}";
    std::string fragmentShader = "precision mediump float;\n"
            "uniform vec4 vColor;\n"
            "void main(){\n"
            "    gl_FragColor = vColor;\n"
            "}";

    int vShader = loadShader(GL_VERTEX_SHADER, vertexShader);
    int fShader = loadShader(GL_FRAGMENT_SHADER, fragmentShader);
    shaderProgramID = createAndLinkProgram(vShader, fShader, (std::string *) "a_Position");

}

int MyLoader::loadShader(unsigned type, std::string shaderCode) {
    unsigned int shader = glCreateShader(type);
    const char *c_str1 = shaderCode.c_str();
    glShaderSource(shader, 1, &c_str1, NULL);
    glCompileShader(shader);
    int *comlile = new int[1];
    glGetShaderiv(shader, GL_COMPILE_STATUS, comlile);
    if (comlile[0] == 0) {
        GLchar *log = new GLchar;
        glGetShaderInfoLog(shader, 0, NULL, log);
        MyLOGE("Error + Could not compile program: %s  |  %s", shaderCode.c_str(), log);
        // for manage memory leak.
        delete log;
    }
    // for manage memory leak.
    delete c_str1;
    delete[] comlile;
    return shader;
}

int MyLoader::createAndLinkProgram(unsigned int vShader, unsigned int fShader,
                                   std::string *attributes) {
    unsigned int programHandel = glCreateProgram();
    if (programHandel != 0) {
        //bind the vertex shader to programHandel.
        glAttachShader(programHandel, vShader);
        //bind the fragment shader to programHandel.
        glAttachShader(programHandel, fShader);
        //bind attribute
        if (attributes != NULL) {
            for (unsigned int i = 0; i < attributes->size(); i++) {
                glBindAttribLocation(programHandel, i, attributes[i].c_str());
            }
        }
        // link the tow shaders (vShader  and fShader) together into program.
        glLinkProgram(programHandel);
        //get the link status.
        int *linkStatus = new int[1];
        glGetProgramiv(programHandel, GL_LINK_STATUS, linkStatus);
        if (linkStatus[0] == 0) {
            GLchar *log = new GLchar;
            glGetProgramInfoLog(programHandel, 0, NULL, log);
            MyLOGE("Error Link + Could not compile program: %s ", log);

            // for manage memory leak.
            glDeleteProgram(programHandel);
            delete log;
            programHandel = 0;
        }
        delete[] linkStatus;
    }


    return programHandel;
}

void MyLoader::GenerateGlBuffer() {
   /* struct Mesh newMesh;
    GLuint bufer;
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh *mesh = scene->mMeshes[i];
        newMesh.mesh = scene->mMeshes[i];
        newMesh.numFaces = mesh->mNumFaces;
        newMesh.numVerts = mesh->mNumVertices;
        newMesh.numNormals = mesh->mNumBones;
        newMesh.numTextures = scene->mNumTextures;
        newMesh.numVertsRefrence = mesh->mNumFaces * 3;
    }*/
}