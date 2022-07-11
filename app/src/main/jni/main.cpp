#include <lightEngine/render/GameSprite.h>
#include <lightEngine/window/AndroidWindow.h>

#include "MyTestGame.hpp"

class TestClass : public Window{
    public:
    void init(GameSprite* gameSprite){
        gameSprite->changedScene(new MyTestGame());
    }
};

void android_main(struct android_app* app){
    AndroidWindow::createWindow(app,new TestClass());
}
