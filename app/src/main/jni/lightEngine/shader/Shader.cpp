#include "Shader.h"
#include <stdio.h>
#include <stdlib.h>

GLuint ShaderUtils::loadShader(GLenum shaderType, const char *pSource)
{
    GLuint shader = 0;
        shader = glCreateShader(shaderType);
        if (shader)
        {
            glShaderSource(shader, 1, &pSource, NULL);
            glCompileShader(shader);
            GLint compiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if (!compiled)
            {
                GLint infoLen = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
                if (infoLen)
                {
                    char* buf = (char*) malloc((size_t)infoLen);
                    if (buf)
                    {
                        glGetShaderInfoLog(shader, infoLen, NULL, buf);
                        /*FILE* f = fopen("/sdcard/1.txt","w");
                        fprintf(f,"%s",buf);
                        fclose(f);*/
                        free(buf);
                    }
                    glDeleteShader(shader);
                    shader = 0;
                }
            }
        }
    return shader;
}

GLuint ShaderUtils::createProgram(const char *pVertexShaderSource, const char *pFragShaderSource, GLuint& vertexShaderHandle, GLuint& fragShaderHandle)
{
    GLuint program = 0;
        vertexShaderHandle = loadShader(GL_VERTEX_SHADER, pVertexShaderSource);
        if (!vertexShaderHandle) return program;

        fragShaderHandle = loadShader(GL_FRAGMENT_SHADER, pFragShaderSource);
        if (!fragShaderHandle) return program;

        program = glCreateProgram();
        if (program)
        {
            glAttachShader(program, vertexShaderHandle);
            checkGLError("glAttachShader");
            glAttachShader(program, fragShaderHandle);
            checkGLError("glAttachShader");
            glLinkProgram(program);
            GLint linkStatus = GL_FALSE;
            glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

            glDetachShader(program, vertexShaderHandle);
            glDeleteShader(vertexShaderHandle);
            vertexShaderHandle = 0;
            glDetachShader(program, fragShaderHandle);
            glDeleteShader(fragShaderHandle);
            fragShaderHandle = 0;
            if (linkStatus != GL_TRUE)
            {
                GLint bufLength = 0;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
                if (bufLength)
                {
                    char* buf = (char*) malloc((size_t)bufLength);
                    if (buf)
                    {
                        glGetProgramInfoLog(program, bufLength, NULL, buf);
                        /*FILE* f = fopen("/sdcard/1.txt","w");
                        fprintf(f,"%s",buf);
                        fclose(f);*/
                        free(buf);
                    }
                }
                glDeleteProgram(program);
                program = 0;
            }
        }
    return program;
}

void ShaderUtils::deleteProgram(GLuint &program)
{
    if (program)
    {
        glUseProgram(0);
        glDeleteProgram(program);
        program = 0;
    }
}

void ShaderUtils::checkGLError(const char *pGLOperation)
{
    for (GLint error = glGetError(); error; error = glGetError())
    {
    }
}

