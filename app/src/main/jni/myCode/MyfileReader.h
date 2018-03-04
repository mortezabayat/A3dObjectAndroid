//
// Created by javan on 3/3/2018.
//

#ifndef DEMOOBJ_FILEREADER_H
#define DEMOOBJ_FILEREADER_H


#include <string>
#include <android/asset_manager.h>
#include <jni.h>
#include <GLES2/gl2.h>
#include "../common/myGLM.h"
#include "myMesh.h"


#define MAX_VERT 100000

struct Vertex {

    float x;
    float y;
    float z;

};

class MyfileReader {
private:
    std::string apkInternalPath;
    AAssetManager *apkAssetManager;

public:
    MyfileReader();

    ~MyfileReader();

    void loade(std::string assetName, std::string &filename);

    void load_obj(std::string assetName, std::string &filename, MyMesh *mesh);


    Vertex vertex[256];
};


#endif //DEMOOBJ_FILEREADER_H
