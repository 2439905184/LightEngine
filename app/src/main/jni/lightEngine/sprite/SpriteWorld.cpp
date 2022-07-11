#include <iostream>
#include "SpriteWorld.h"
#include "SpriteActor.h"

SpriteWorld::SpriteWorld(){
    
}

void SpriteWorld::update(Scene* scene){
    allActors = scene->allSpriteActors;
    for(int i = 0;i < allActors.size();i++){
        bool isCollision = allActors[i]->getUseSpriteCollision();
        if(isCollision){
            SpriteActor* collisionActor = allActors[i];
            for(int j = 0;j < allActors.size();j++){
                bool isCollision2 = allActors[j]->getUseSpriteCollision();
                if(isCollision2){
                    SpriteActor* collisionActor2 = allActors[j];
                    if(collisionActor != collisionActor2){
                        if(SpriteCollision::getSpriteCollision()->testAABB(collisionActor,collisionActor2)){
                            resolveCollision(collisionActor,collisionActor2);
                        }
                    }
                }
            }
        }
    }
}

void SpriteWorld::resolveCollision(SpriteActor* actor1,SpriteActor* actor2){
    actor1->onCollision(actor2);
    actor2->onCollision(actor1);
}
