#include "AndroidWindow.h"
#include <lightEngine/file/File.h>
#include <lightEngine/render/GameSprite.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Create_Native_Activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Create_Native_Activity", __VA_ARGS__))

static GameSprite* gameSprite = 0;
static Window* androidWindow = 0;
static bool init = false;

static int engine_init_display(struct App* app) {
    const EGLint attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 8,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE
    };

    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(app->app->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config, app->app->window, NULL);
    
    EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };

    context = eglCreateContext(display, config, NULL, contextAttribs);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        return -1;
    }
    
    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    app->display = display;
    app->context = context;
    app->surface = surface;
    app->width = w;
    app->height = h;
    
    glDepthFunc(GL_LEQUAL);
    
    if(gameSprite == 0){
        gameSprite = GameSprite::getGameSprite();
    }

    gameSprite->init(w,h);
    
    if(!init&&androidWindow){
        androidWindow->init(gameSprite);
        init = true;
    }
    
    app->state.angle = 0;
    
    return 0;
}

static void engine_draw_frame(struct App* app) {
    if (app->display == NULL) {
        return;
    }
    
    if(gameSprite)
        gameSprite->update();
    
    eglSwapBuffers(app->display, app->surface);
}

static void engine_term_display(struct App* app) {
    if (app->display != EGL_NO_DISPLAY) {
        eglMakeCurrent(app->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (app->context != EGL_NO_CONTEXT) {
            eglDestroyContext(app->display, app->context);
        }
        if (app->surface != EGL_NO_SURFACE) {
            eglDestroySurface(app->display, app->surface);
        }
        eglTerminate(app->display);
    }
    
    app->animating = 0;
    app->display = EGL_NO_DISPLAY;
    app->context = EGL_NO_CONTEXT;
    app->surface = EGL_NO_SURFACE;
}

static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {

    struct App* app_ = (struct App*)app->userData;
    int action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
    
    int EventType = AInputEvent_getType(event);
    if (EventType == AINPUT_EVENT_TYPE_MOTION)
    {
        if(gameSprite){
            gameSprite->onTouch(event);
        }
        
        if (action == AMOTION_EVENT_ACTION_MOVE) {
            app_->state.x = AMotionEvent_getX(event, 0);
            app_->state.y = AMotionEvent_getY(event, 0);
        }
        
        return 1;
    }
    
    return 0;
}

static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
    struct App* app_ = (struct App*)app->userData;
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            app_->app->savedState = malloc(sizeof(struct saved_state));
            *((struct saved_state*)app_->app->savedState) = app_->state;
            app_->app->savedStateSize = sizeof(struct saved_state);
            break;
        case APP_CMD_INIT_WINDOW:
            if (app_->app->window != NULL){
                engine_init_display(app_);
                
                engine_draw_frame(app_);
            }
            break;
        case APP_CMD_TERM_WINDOW:
            engine_term_display(app_);
            break;
        case APP_CMD_GAINED_FOCUS:
            if (app_->accelerometerSensor != NULL) {
                ASensorEventQueue_enableSensor(app_->sensorEventQueue,
                        app_->accelerometerSensor);
                ASensorEventQueue_setEventRate(app_->sensorEventQueue,
                        app_->accelerometerSensor, (1000L/60)*1000);
            }
            break;
        case APP_CMD_LOST_FOCUS:
            if (app_->accelerometerSensor != NULL) {
                ASensorEventQueue_disableSensor(app_->sensorEventQueue,
                        app_->accelerometerSensor);
            }
            engine_draw_frame(app_);
            break;
        case APP_CMD_PAUSE:
            if(gameSprite){
                gameSprite->onPause();
            }
            app_->animating = 0;
        break;
        
        case APP_CMD_RESUME:
            if(gameSprite){
                gameSprite->onResume();
            }
            app_->animating = 1;
        break;
        
        case APP_CMD_DESTROY:
            if(gameSprite){
                gameSprite->destroy();
                delete[] gameSprite;
                gameSprite = 0;
            }
        break;
    }
}

void AndroidWindow::createWindow(struct android_app* state,Window* window){
    struct App app;

    app_dummy();

    androidWindow = window;
    
    memset(&app, 0, sizeof(app));
    state->userData = &app;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;
    app.app = state;
    app.animating = 1;
    
    File::getFile()->assetManager = state->activity->assetManager;
    
    app.sensorManager = ASensorManager_getInstance();
    app.accelerometerSensor = ASensorManager_getDefaultSensor(app.sensorManager,
            ASENSOR_TYPE_ACCELEROMETER);
    app.sensorEventQueue = ASensorManager_createEventQueue(app.sensorManager,
            state->looper, LOOPER_ID_USER, NULL, NULL);

    if (state->savedState != NULL) {
        app.state = *(struct saved_state*)state->savedState;
    }

    while(1){
        int ident;
        int events;
        struct android_poll_source* source;

        while((ident=ALooper_pollAll(app.animating ? 0 : -1, NULL, &events,
        (void**)&source)) >= 0) {

            if (source != NULL) {
                source->process(state, source);
            }

            if (ident == LOOPER_ID_USER) {
                if (app.accelerometerSensor != NULL) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(app.sensorEventQueue,
                            &event, 1) > 0) {
                    }
                }
            }

            if (state->destroyRequested != 0) {
                engine_term_display(&app);
                return;
            }
        }
        
        if (app.animating) {
            app.state.angle += .01f;
                if (app.state.angle > 1) {
                        app.state.angle = 0;
                }
            engine_draw_frame(&app);
        }
    }
}

