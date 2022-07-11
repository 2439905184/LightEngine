#ifndef ANDROID_WINDOW_H
#define ANDROID_WINDOW_H

#include <lightEngine/Scene.h>
#include "Window.h"
#include <GLES3/gl3.h>
#include <android/input.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <android/sensor.h>
#include <errno.h>
#include <android_native_app_glue.h>

struct saved_state{
    float angle;
    int32_t x;
    int32_t y;
};

struct App{
    struct android_app* app;
    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;
    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    struct saved_state state;
};

class AndroidWindow{
    public:
    static void createWindow(struct android_app* app,Window* window);
};

#endif
