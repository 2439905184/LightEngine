LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPP_EXTENSION := .cpp .cc .cxx
LOCAL_MODULE := LightEngine

LOCAL_SRC_FILES := \
        main.cpp \
        lightEngine/glm/detail/glm.cpp \
        lightEngine/file/File.cpp \
        lightEngine/sprite/SpriteActor.cpp \
        lightEngine/sprite/SpriteWorld.cpp \
        lightEngine/collision/SpriteCollision.cpp \
        lightEngine/render/GameSprite.cpp \
        lightEngine/time/DeltaTime.cpp \
        lightEngine/vertices/vertices2d.cpp \
        lightEngine/window/ScreenWindow.cpp \
        lightEngine/window/AndroidWindow.cpp \
        lightEngine/texture/image/stb_image.cpp \
        lightEngine/texture/Texture.cpp \
        lightEngine/shader/Shader.cpp \
        
LOCAL_LDLIBS := -ldl -llog -landroid -lEGL -lGLESv3 -lOpenSLES

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH) \
    $(LOCAL_PATH)/lightEngine \
    $(LOCAL_PATH)/lightEngine/glm
    
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)

