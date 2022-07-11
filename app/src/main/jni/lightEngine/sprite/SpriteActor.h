#ifndef SPRITE_ACTOR_H
#define SPRITE_ACTOR_H

#include <lightEngine/texture/Texture.h>
#include <lightEngine/shader/Shader.h>
#include <lightEngine/vertices/vertices2d_helper.h>
#include <lightEngine/window/ScreenWindow.h>

class SpriteActor{
    private:
    char* name;
    bool useTexture = true;
    Texture* spriteTexture;
    glm::vec2 position;
    glm::vec2 size;
    glm::vec4 color;
    Shader* shader;
    glm::vec4 aabbSprite;
    Vertices2d* sprite_vertices;
    bool use_dic = true;
    bool use_color = false;
    float transparency_value = 0;
    float texture_x = 1,texture_y = 1;
    float offset_x = 0,offset_y = 0;
    bool useSpriteCollision = true;
    float Z = 1.0;
    public:
    SpriteActor(char* sprireName);
    SpriteActor(char* spriteName,Texture* texture);
    ~SpriteActor();
    
    void setPosition(glm::vec2 position);
    void setPosition(float x,float y);
    void setSize(glm::vec2 size);
    void setSize(float width,float height);
    void setWidth(float width);
    void setHeight(float height);
    void setColor(glm::vec4 color);
    void setTexture(Texture* texture);
    void setTransparency(float a);
    void setBoolDiscard(bool dic);
    void setOffsetTexture(glm::vec4 offset);
    void setZ(float z);
    void setOffsetTexture(float x,float y,float z,float w);
    void render();
    void setUseSpriteCollision(bool useAABB);
    
    bool getUseSpriteCollision();
    glm::vec4 getAABBPoint();
    char* getName() const;
    glm::vec2 getPosition() const;
    glm::vec2 getSize() const;
    float getWidth() const;
    float getHeight() const;
    glm::vec4 getColor() const;
    Texture* getTexture() const;
    
    virtual void onCollision(SpriteActor* collision){};
    virtual void update(){};
};

#endif
