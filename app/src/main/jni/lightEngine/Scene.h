#ifndef SCENE_H
#define SCENE_H

#include "sprite/SpriteActor.h"
#include <vector>

class GameSprite;

class Scene{
    private:
    GameSprite* gameApplication;
    public:
    std::vector<SpriteActor*> allSpriteActors;
    virtual void init(int w,int h) = 0;
    virtual void update(float delta) = 0;
    virtual void destroy() = 0;
    virtual void onTouch(int action,float x,float y){}
    virtual void onResume(){}
    virtual void onPause(){}
    
    void render(){
        if(allSpriteActors.size() != 0){
            for (int i = 0; i < allSpriteActors.size(); i++){
                allSpriteActors[i]->render();
                allSpriteActors[i]->update();
            }
        }
    }
    
    void setGameSprite(GameSprite* sprite){
        gameApplication = sprite;
    }
    
    GameSprite* getGameSprite(){
        return gameApplication;
    }
    
    void addSprite(SpriteActor* actor){
        allSpriteActors.push_back(actor);
    }
};

#endif
