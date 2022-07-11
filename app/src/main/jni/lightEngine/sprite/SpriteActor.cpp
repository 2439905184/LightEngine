#include "SpriteActor.h"

SpriteActor::~SpriteActor(){
    delete[] spriteTexture;
    spriteTexture = 0;
    sprite_vertices->destroy();
    
}

SpriteActor::SpriteActor(char* name){
    this->name = name;
    this->useTexture = false;
    
    sprite_vertices = Vertices2d_Helper::createQuad();
    
    char* sprite_vertex = "#version 300 es\n"
                          "layout(location = 0) in vec2 position;\n"
                          "layout(location = 1) in vec2 texCoord;\n"
                          "uniform mat4 matrix_formsprite;\n"
                          "out vec2 v_texCoord;\n"
                          "void main(){\n"
                          "    v_texCoord = texCoord;\n"
                          "    gl_Position = matrix_formsprite * vec4(position.xy, 0.0, 1.0);\n"
                          "}\n";
    //
    char* sprite_fragment = "#version 300 es\n"
                            "#ifdef GL_FRAGMENT_PRECISION_HIGH\n"
                            "precision highp float;\n"
                            "#else\n"
                            "precision mediump float;\n"
                            "#endif\n"
                            "in vec2 v_texCoord;\n"
                            "uniform sampler2D sprite_texture;\n"
                            "out vec4 fragColor;\n"
                            "uniform vec4 u_tiling_offset;\n"
                            "uniform bool use_texture;\n"
                            "uniform bool use_discard;\n"
                            "uniform bool use_color;\n"
                            "uniform vec4 color_value;\n"
                            "uniform float Valuetransparency;\n"
                            "vec4 imageMap;"
                            "void main(){\n"
                            "    if(use_texture){\n"
                            "        vec2 texCoord = v_texCoord * u_tiling_offset.xy + u_tiling_offset.zw;\n"
                            "    if(use_color){\n"
                            "        imageMap = texture(sprite_texture, texCoord) * color_value;\n"
                            "    }\n"
                            "    else if(!use_color){\n"
                            "        imageMap = texture(sprite_texture, texCoord);\n"
                            "    }\n"
                            "        if(imageMap.a < 0.5&&use_discard){\n"
                            "            discard;\n"
                            "        }\n"
                            "        if(!use_discard){\n"
                            "            imageMap.a *= Valuetransparency;\n"
                            "        }\n"
                            "        fragColor = imageMap;\n"
                            "    }\n"
                            "    else if(use_color){\n"
                            "        fragColor = color_value;\n"
                            "    }\n"
                            "}\n";
                            
                            
    shader = new Shader(sprite_vertex,sprite_fragment);
    shader->use();
    shader->setInt("sprite_texture",0);

}

SpriteActor::SpriteActor(char* name,Texture* texture){
    this->name = name;
    texture->init();
    this->spriteTexture = texture;
    
    sprite_vertices = Vertices2d_Helper::createQuad();
    
    char* sprite_vertex = "#version 300 es\n"
                          "layout(location = 0) in vec2 position;\n"
                          "layout(location = 1) in vec2 texCoord;\n"
                          "uniform mat4 matrix_formsprite;\n"
                          "out vec2 v_texCoord;\n"
                          "void main(){\n"
                          "    v_texCoord = texCoord;\n"
                          "    gl_Position = matrix_formsprite * vec4(position.xy, 0.0, 1.0);\n"
                          "}\n";
    //
    char* sprite_fragment = "#version 300 es\n"
                            "#ifdef GL_FRAGMENT_PRECISION_HIGH\n"
                            "precision highp float;\n"
                            "#else\n"
                            "precision mediump float;\n"
                            "#endif\n"
                            "in vec2 v_texCoord;\n"
                            "uniform sampler2D sprite_texture;\n"
                            "out vec4 fragColor;\n"
                            "uniform vec4 u_tiling_offset;\n"
                            "uniform bool use_texture;\n"
                            "uniform bool use_discard;\n"
                            "uniform bool use_color;\n"
                            "uniform vec4 color_value;\n"
                            "uniform float Valuetransparency;\n"
                            "vec4 imageMap;"
                            "void main(){\n"
                            "    if(use_texture){\n"
                            "        vec2 texCoord = v_texCoord * u_tiling_offset.xy + u_tiling_offset.zw;\n"
                            "    if(use_color){\n"
                            "        imageMap = texture(sprite_texture, texCoord) * color_value;\n"
                            "    }\n"
                            "    else if(!use_color){\n"
                            "        imageMap = texture(sprite_texture, texCoord);\n"
                            "    }\n"
                            "        if(imageMap.a < 0.5&&use_discard){\n"
                            "            discard;\n"
                            "        }\n"
                            "        if(!use_discard){\n"
                            "            imageMap.a *= Valuetransparency;\n"
                            "        }\n"
                            "        fragColor = imageMap;\n"
                            "    }\n"
                            "    else if(use_color){\n"
                            "        fragColor = color_value;\n"
                            "    }\n"
                            "}\n";
                            
                            
    shader = new Shader(sprite_vertex,sprite_fragment);
    shader->use();
    shader->setInt("sprite_texture",0);

}

void SpriteActor::render(){
    
    shader->use();
    
    shader->setBool("use_texture",useTexture);
    shader->setBool("use_discard",use_dic);
    shader->setBool("use_color",use_color);
    
    shader->setVec4("color_value",glm::vec4(color.x,color.y,color.z,color.w));
    shader->setFloat("Valuetransparency",transparency_value);
    
    shader->setVec4("u_tiling_offset",glm::vec4(1 / texture_x,1 / texture_y,offset_x / texture_x,offset_y / texture_y));
    
    glm::mat4 projection = glm::ortho(0.0f,(float)ScreenWindow::getScreenWindow()->getScreenWidth(),(float)ScreenWindow::getScreenWindow()->getScreenHeight(),0.0f,-1.0f,1.0f);
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(this->position.x-(this->size.x/2.0f),this->position.y-(this->size.y/2.0f), Z));
    model = glm::scale(model, glm::vec3(this->size.x,this->size.y, 0.0));
    glm::mat4 mvpMatrix = projection * model;
    
    shader->setMat4("matrix_formsprite",mvpMatrix);
    
    if(useTexture){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, spriteTexture->getId());
    }
    
    sprite_vertices->render(GL_TRIANGLES);
    
    aabbSprite.x = this->position.x-(this->size.x/2.0f);
    aabbSprite.y = this->position.x+(this->size.x/2.0f);
    aabbSprite.z = this->position.y-(this->size.y/2.0f);
    aabbSprite.w = this->position.y+(this->size.y/2.0f);
}

void SpriteActor::setPosition(glm::vec2 position){
    this->position = position;
}

void SpriteActor::setPosition(float x,float y){
    this->setPosition(glm::vec2(x,y));
}

void SpriteActor::setSize(glm::vec2 size){
    this->size = size;
}

void SpriteActor::setTransparency(float a){
    this->use_dic = false;
    this->transparency_value = a;
}

void SpriteActor::setBoolDiscard(bool dic){
    this->use_dic = dic;
}

void SpriteActor::setSize(float width,float height){
    this->setSize(glm::vec2(width,height));
}

void SpriteActor::setZ(float z){
    this->Z = z;
}

void SpriteActor::setColor(glm::vec4 color){
    this->use_color = true;
    this->color = color;
}

void SpriteActor::setUseSpriteCollision(bool useAABB){
    this->useSpriteCollision = useAABB;
}

void SpriteActor::setOffsetTexture(glm::vec4 offset){
    this->texture_x = offset.x;
    this->texture_y = offset.y;
    this->offset_x = offset.z;
    this->offset_y = offset.w;
}

void SpriteActor::setOffsetTexture(float x,float y,float z,float w){
    this->texture_x = x;
    this->texture_y = y;
    this->offset_x = z;
    this->offset_y = w;
}

void SpriteActor::setTexture(Texture* texture){
    if(!useTexture){
        useTexture = true;
    }
    texture->init();
    spriteTexture = texture;
}

char* SpriteActor::getName() const{
    return this->name;
}

bool SpriteActor::getUseSpriteCollision(){
    return this->useSpriteCollision;
}

glm::vec4 SpriteActor::getAABBPoint(){
    return this->aabbSprite;
}

glm::vec2 SpriteActor::getPosition() const{
    return this->position;
}

glm::vec2 SpriteActor::getSize() const{
    return this->size;
}

glm::vec4 SpriteActor::getColor() const{
    return this->color;
}

Texture* SpriteActor::getTexture() const{
    return this->spriteTexture;
}
