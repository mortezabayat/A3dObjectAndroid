#include "modelAssimp.h"
#include "../common/myJNIHelper.h"

//#include <opencv2/opencv.hpp>

/**
 * Class constructor
 */
ModelAssimp::ModelAssimp() {
    initsDone = false;
    // create MyGLCamera object and set default position for the object
    myGLCamera = new MyGLCamera();
    float pos[] = {0., 0., 0., 0.2, 0.5, 0.};
    std::copy(&pos[0], &pos[5], std::back_inserter(modelDefaultPosition));
    myGLCamera->SetModelPosition(modelDefaultPosition);

}

ModelAssimp::~ModelAssimp() {

    if (myGLCamera) {
        delete myGLCamera;
    }
    if (modelObject) {
        delete modelObject;
    }
}

/**
 * Perform inits and load the triangle's vertices/colors to GLES
 */
void ModelAssimp::PerformGLInits() {

    MyLOGD("ModelAssimp::PerformGLInits");

    MyGLInits();

    modelObject = new AssimpLoader();

    // extract the OBJ and companion files from assets // humvee
    std::string objFilename, mtlFilename, texFilename;//cube2
    bool isFilesPresent =
            gHelperObject->ExtractAssetReturnFilename("amenemhat/cube1.obj", objFilename) &&
            gHelperObject->ExtractAssetReturnFilename("amenemhat/cube1.obj.mtl", mtlFilename) &&
            gHelperObject->ExtractAssetReturnFilename("amenemhat/cube.bmp", texFilename);
    if (!isFilesPresent) {
        MyLOGE("Model %s does not exist!", objFilename.c_str());
        return;
    }

   // myfileReader = new MyfileReader();
    //myfileReader->load_obj("amenemhat/cube1.obj", objFilename, mesh);

   // mesh->object2world = glm::mat4(1);
   // this->MyRender(mesh);
    modelObject->Load3DModel(objFilename);

    CheckGLError("ModelAssimp::PerformGLInits");
    initsDone = true;
}

void ModelAssimp::MyRender(MyMesh *mesh) {
    //mesh->upload();
    ///this->Render();
}

/**
 * Render to the display
 */
void ModelAssimp::Render() {

    // clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (mesh == NULL)
        mesh = new MyMesh();
    glm::mat4 mvpMat = myGLCamera->GetMVP();
    modelObject->Render3DModel( &mvpMat);
    CheckGLError("ModelAssimp::Render");
}

/**
 * set the viewport, function is also called when user changes device orientation
 */
void ModelAssimp::SetViewport(int width, int height) {

    screenHeight = height;
    screenWidth = width;
    glViewport(0, 0, width, height);
    CheckGLError("Cube::SetViewport");
    myGLCamera->SetAspectRatio((float) width / height);
}

/**
 * reset model's position in double-tap
 */
void ModelAssimp::DoubleTapAction() {
    myGLCamera->SetModelPosition(modelDefaultPosition);
}

/**
 * rotate the model if user scrolls with one finger
 */
void ModelAssimp::ScrollAction(float distanceX, float distanceY, float positionX, float positionY) {

    myGLCamera->RotateModel(distanceX, distanceY, positionX, positionY);
}

/**
 * pinch-zoom: move the model closer or farther away
 */
void ModelAssimp::ScaleAction(float scaleFactor) {

    myGLCamera->ScaleModel(scaleFactor);
}

/**
 * two-finger drag: displace the model by changing its x-y coordinates
 */
void ModelAssimp::MoveAction(float distanceX, float distanceY) {

    myGLCamera->TranslateModel(distanceX, distanceY);
}
