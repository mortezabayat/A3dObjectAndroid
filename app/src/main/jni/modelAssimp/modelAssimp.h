//
// Created by javan on 2/24/2018.
//

#ifndef MODELASSIMP_H
#define MODELASSIMP_H


#include <GLES2/gl2.h>
#include "../common/myGLCamera.h"
#include "../myCode/myMesh.h"
#include "../common/assimpLoader.h"
#include "../myCode/MyfileReader.h"

class ModelAssimp {
public:
    GLuint program;
    GLint attribute_v_coord = -1;
    GLint attribute_v_normal = -1;

    AssimpLoader *modelObject = NULL;
    MyfileReader  *myfileReader;
    ModelAssimp();

    ~ModelAssimp();

    void PerformGLInits();

    void Render();

    void MyRender(MyMesh *mesh);

    void SetViewport(int width, int height);

    void DoubleTapAction();

    void ScrollAction(float distanceX, float distanceY, float positionX, float positionY);

    void ScaleAction(float scaleFactor);

    void MoveAction(float distanceX, float distanceY);

    int GetScreenWidth() const { return screenWidth; }

    int GetScreenHeight() const { return screenHeight; }

    MyMesh *mesh;

private:


    bool initsDone;
    int screenWidth, screenHeight;

    std::vector<float> modelDefaultPosition;
    MyGLCamera *myGLCamera;
    //AssimpLoader *modelObject;
};

#endif //MODELASSIMP_H