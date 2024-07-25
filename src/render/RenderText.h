//
// Created by habi on 7/25/2024.
//
#ifndef RENDERTEXT_H
#define RENDERTEXT_H

#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

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
    RenderText(const char *vertexPath, const char *fragmentPath, glm::mat4 projection, unsigned int fontSize = 20);
    ~RenderText();

    void render_text(std::string text, float x, float y, float scale, glm::vec3 color);
    void set_font_size(unsigned int size);

private:
    void load_font();

    unsigned int mVAO;
    unsigned int mVBO;

    std::string mFont;
    unsigned int mFontSize;
    std::map<char, FontChar> mFontChars;
    Shader *mShader;

    FT_Library mFTLibrary;
    FT_Face mFTFace;
};


#endif // RENDERTEXT_H
