#include "GameSprite.h"

GameSprite* GameSprite::getGameSprite(){
    static GameSprite* gameSprite;
    if(gameSprite == 0){
        gameSprite = new GameSprite();
    }
    return gameSprite;
}

void GameSprite::changedScene(Scene* newScene){
    this->scene = newScene;
    this->scene->setGameSprite(this);
}

void GameSprite::init(int w,int h){
    DeltaTime::getDeltaTimeClass()->init();
    
    ScreenWindow::getScreenWindow()->setScreenWidth(w);
    ScreenWindow::getScreenWindow()->setScreenHeight(h);
    
    if(scene != 0){
        scene->init(ScreenWindow::getScreenWindow()->width,ScreenWindow::getScreenWindow()->height);
    }
}

void GameSprite::update(){
    DeltaTime::getDeltaTimeClass()->update();
    
    if(scene != 0 && !changed){
        if(init_first){
            init_first = false;
            scene->init(ScreenWindow::getScreenWindow()->width,ScreenWindow::getScreenWindow()->height);
        }
        
        scene->render();
        scene->update(DeltaTime::getDeltaTimeClass()->getDeltaTime());
        
	}
}

void GameSprite::onPause(){
    changed = true;
    if(scene != 0){
        scene->onPause();
    }
}

void GameSprite::onResume(){
    changed = false;
    if(scene != 0){
        scene->onResume();
    }
}

void GameSprite::onTouch(AInputEvent* event){
    int action_ = AMotionEvent_getAction(event);
    int action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
    size_t pointer_ = (size_t)((action_ & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT);
    float x = AMotionEvent_getX(event,pointer_);
    float y = AMotionEvent_getY(event,pointer_);
    scene->onTouch(action,x,y);
}

void GameSprite::destroy(){
    if(scene != 0){
        scene->destroy();
    }
}
