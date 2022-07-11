#ifndef VERTICES_2D_H
#define VERTICES_2D_H

#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

class Vertices2d{
    private:
    GLuint vbo;
    int size;
    public:
    Vertices2d(float* vertices,int);
    void render(GLint mode);
    void destroy();
};

#endif
