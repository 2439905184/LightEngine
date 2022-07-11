#ifndef VERTICES_2D_HELPER_H
#define VERTICES_2D_HELPER_H

#include "vertices2d.h"
#include <lightEngine/glm/glm.hpp>
#include <lightEngine/glm/gtc/matrix_transform.hpp>
#include <lightEngine/glm/ext/matrix_clip_space.hpp>
#include <lightEngine/glm/gtc/type_ptr.hpp>

struct Vertex2f{
    glm::vec2 vertex;
    glm::vec2 texCoord;
    Vertex2f(){}
    Vertex2f(glm::vec2 vertex){
        this->vertex = vertex;
    }
    Vertex2f(glm::vec2 vertex,glm::vec2 texCoord){
        this->vertex = vertex;
        this->texCoord = texCoord;
    }
};

class Vertices2d_Helper{
    public:
    static Vertices2d* getVertices2d(Vertex2f* vertices2f,int verticesNum){
        float* vertices = new float[verticesNum * 4];
        for (int i = 0; i < verticesNum; i++){
            vertices[i * 4 + 0] = vertices2f[i].vertex.x;
            vertices[i * 4 + 1] = vertices2f[i].vertex.y;
            vertices[i * 4 + 2] = vertices2f[i].texCoord.x;
            vertices[i * 4 + 3] = vertices2f[i].texCoord.y;
        }
        Vertices2d* vertices2d = new Vertices2d(vertices,verticesNum);
        return vertices2d;
    }
    
    static Vertices2d* createQuad(){
        static Vertex2f* quadVertices;
        if(quadVertices == NULL){
            quadVertices = new Vertex2f[6];
            
            quadVertices[0] = Vertex2f(glm::vec2(0.0,0.0), glm::vec2(0.0,0.0));
            quadVertices[1] = Vertex2f(glm::vec2(0.0,1.0), glm::vec2(0.0,1.0));
            quadVertices[2] = Vertex2f(glm::vec2(1.0,0.0), glm::vec2(1.0,0.0));

            quadVertices[3] = Vertex2f(glm::vec2(0.0,1.0), glm::vec2(0.0,1.0));
            quadVertices[4] = Vertex2f(glm::vec2(1.0,1.0), glm::vec2(1.0,1.0));
            quadVertices[5] = Vertex2f(glm::vec2(1.0,0.0), glm::vec2(1.0,0.0));
            
        }
        return getVertices2d(&quadVertices[0],6);
    }
};

#endif
