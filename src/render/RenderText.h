//
// Created by habi on 7/25/2024.
//
#ifndef RENDERTEXT_H
#define RENDERTEXT_H

#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"


struct FontChar
{
    unsigned int textureID;
    glm::fvec2 size;
    glm::fvec2 bearing;
    unsigned int advance;
};


class RenderText
{
public:
    RenderText(const char *vertexPath, const char *fragmentPath, glm::mat4 projection);
    ~RenderText();

    void render_text(std::string text, float x, float y, float scale, glm::vec3 color);

private:
    void loadFreetype();

    unsigned int mVAO, mVBO;
    std::map<char, FontChar> mFontChars;
    Shader *mShader;
};


#endif // RENDERTEXT_H
