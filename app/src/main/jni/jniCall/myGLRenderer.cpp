//
// Created by javan on 2/24/2018.
//

#include <jni.h>
#include "../modelAssimp/modelAssimp.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ModelAssimp *gAssimpObject;

JNIEXPORT void JNICALL
Java_com_example_javan_demoobj_MyGLRenderer_DrawFrameNative(JNIEnv *env, jobject instance) {

    if (gAssimpObject == NULL) {
        return;
    }
    gAssimpObject->Render();

}

JNIEXPORT void JNICALL
Java_com_example_javan_demoobj_MyGLRenderer_SurfaceCreatedNative(JNIEnv *env, jobject instance) {
    if (gAssimpObject == NULL) {
        return;
    }
    gAssimpObject->PerformGLInits();
}

JNIEXPORT void JNICALL
Java_com_example_javan_demoobj_MyGLRenderer_SurfaceChangedNative(JNIEnv *env,
                                                                              jobject instance,
                                                                              jint width,
                                                                              jint height) {
    if (gAssimpObject == NULL) {
        return;
    }
    gAssimpObject->SetViewport(width, height);
}

#ifdef __cplusplus
}
#endif