package com.example.javan.demoobj;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by javan on 2/21/2018.
 */

public class MyGLRenderer implements GLSurfaceView.Renderer {


    private native void DrawFrameNative();

    private native void SurfaceCreatedNative();

    private native void SurfaceChangedNative(int w, int h);

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        SurfaceCreatedNative();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        SurfaceChangedNative(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        DrawFrameNative();
        //new DrawObj().draw(gl);
    }
}
