#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "../Scene.h"
#include "../time/DeltaTime.h"
#include "../window/ScreenWindow.h"
#include <android/input.h>

class GameSprite{
    private:
    Scene* scene;
    bool changed = false;
    bool init_first = true;
    public:
    static GameSprite* getGameSprite();
    void changedScene(Scene* scene);
    void init(int w,int h);
    void onTouch(AInputEvent* e);
    void onResume();
    void onPause();
    void update();
    void destroy();
};

#endif
