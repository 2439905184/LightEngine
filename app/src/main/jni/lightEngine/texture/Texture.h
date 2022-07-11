#ifndef TEXTURE_H
#define TEXTURE_H

#include <lightEngine/file/File.h>
#include <GLES3/gl3.h>

class Texture{
    public:
    GLuint id;
    unsigned char *image;
    GLint width,height;
    bool id_bool = false;
    int n;
    public:
    Texture(const char* path);
    Texture(GLuint id);
    ~Texture();
    void init();
    GLuint getId() const;
};

#endif
