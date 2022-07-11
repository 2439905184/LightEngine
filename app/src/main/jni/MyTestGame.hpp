#ifndef MY_TEST_GAME_HPP
#define MY_TEST_GAME_HPP

#include <lightEngine/Scene.h>
#include <lightEngine/sprite/SpriteActor.h>

class MyTestGame : public Scene{
    public:
    void init(int width,int height){
        SpriteActor* actor = new SpriteActor("我的精灵");
        actor->setSize(200.0,200.0);
        actor->setPosition(200.0,200.0);
        actor->setColor(glm::vec4(1.0,0.0,0.0,1.0));
        addSprite(actor);
    }
    
    void update(float delta){
        
    }
    
    void onTouch(int action,float x,float y){
        
    }
    
    void destroy(){
        
    }
};

#endif
