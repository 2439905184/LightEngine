#ifndef SPRITE_WORLD_H
#define SPRITE_WORLD_H

#include <lightEngine/collision/SpriteCollision.h>
#include <lightEngine/Scene.h>

class SpriteWorld{
    private:
    std::vector<SpriteActor*> allActors;
    public:
    SpriteWorld();
    void update(Scene* scene);
    void resolveCollision(SpriteActor* actor1,SpriteActor* actor2);
};

#endif
