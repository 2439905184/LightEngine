#include "Texture.h"

Texture::Texture(const char* path){
   File::getFile()->readAssetTexture(path,&width,&height,&n,&image);
   
   glActiveTexture(GL_TEXTURE0);
   glGenTextures(1, &id);
   glBindTexture(GL_TEXTURE_2D, id);
   glGenerateMipmap(GL_TEXTURE_2D);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture::Texture(GLuint id){
    this->id_bool = true;
    this->id = id;
}

void Texture::init(){

   if(!id_bool){
   GLenum format;
        if (n == 1)
            format = GL_RED;
        else if (n == 3)
            format = GL_RGB;
        else if (n == 4)
            format = GL_RGBA;
            
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, id);
   glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
   glBindTexture(GL_TEXTURE_2D, GL_NONE);
   
   image = 0;
   delete[] image;
   }
}

Texture::~Texture(){
    id = 0;
    width = 0;
    height = 0;
}

GLuint Texture::getId() const{
    return this->id;
}
