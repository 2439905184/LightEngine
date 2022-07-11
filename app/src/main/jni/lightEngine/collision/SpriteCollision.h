#ifndef SPRITE_COLLISION_H
#define SPRITE_COLLISION_H

//向量四碰撞对照表
//x = minX,y = maxX,z = minY,w = maxY

class SpriteActor;

class SpriteCollision{
    public:
    static SpriteCollision* getSpriteCollision();
    
    bool inBounds(SpriteActor* actor,float x,float y);
    bool testAABB(SpriteActor* actor,SpriteActor* actor2);
};

#endif
