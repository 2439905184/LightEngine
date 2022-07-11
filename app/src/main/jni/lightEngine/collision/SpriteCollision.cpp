#include "SpriteCollision.h"
#include <lightEngine/sprite/SpriteActor.h>

SpriteCollision* SpriteCollision::getSpriteCollision(){
    static SpriteCollision* spriteCollisionClass;
    if(spriteCollisionClass == 0){
        spriteCollisionClass = new SpriteCollision();
    }
    return spriteCollisionClass;
}

bool SpriteCollision::inBounds(SpriteActor* actor,float x,float y){
    glm::vec4 aabbSprite = actor->getAABBPoint();
    return ((x >= aabbSprite.x && x <= aabbSprite.y) & (y >= aabbSprite.z && y <= aabbSprite.w));
}

bool SpriteCollision::testAABB(SpriteActor* actor,SpriteActor* actor2){

    if (actor->getAABBPoint().y < actor2->getAABBPoint().x) return false;
    if (actor->getAABBPoint().x > actor2->getAABBPoint().y) return false;
    if (actor->getAABBPoint().w < actor2->getAABBPoint().z) return false;
    if (actor->getAABBPoint().z > actor2->getAABBPoint().w) return false;
    
    return true;
}
