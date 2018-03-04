//
// Created by javan on 2/24/2018.
//

#include <jni.h>
#include "../myCode/MyfileReader.h"
#include "../common/myJNIHelper.h"
#include "../modelAssimp/modelAssimp.h"

#ifdef __cplusplus
extern "C" {
#endif


// global pointer is used in JNI calls to reference to same object of type Cube
ModelAssimp *gAssimpObject = NULL;

// global pointer to instance of MyJNIHelper that is used to read from assets
MyJNIHelper *gHelperObject = NULL;


JNIEXPORT void JNICALL
Java_com_example_javan_demoobj_MainActivity_CreateObjectNative(JNIEnv *env, jobject instance,
                                                               jobject assetManager,
                                                               jstring pathToInternalDir) {
    gHelperObject = new MyJNIHelper(env, instance, assetManager, pathToInternalDir);
    gAssimpObject = new ModelAssimp();

}

JNIEXPORT void JNICALL
Java_com_example_javan_demoobj_MainActivity_DeleteObjectNative(JNIEnv *env, jobject instance) {

    if (gAssimpObject != NULL) {
        delete gAssimpObject;
    }
    gAssimpObject = NULL;

    if (gHelperObject != NULL) {
        delete gHelperObject;
    }
    gHelperObject = NULL;
}

#ifdef __cplusplus
}
#endif