#ifndef RENDERTEXT_H
#define RENDERTEXT_H

#include <map>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"


struct FontChar
{
    unsigned int texture_id;
    glm::fvec2 size;
    glm::fvec2 bearing;
    unsigned int advance;
};

struct WindowSize
{
    int width;
    int height;
};


class RenderText
{
public:
    RenderText(GLFWwindow *window, const char *vertex_path, const char *fragment_path, unsigned int font_size = 20);
    ~RenderText();

    void renderText(std::string text, float x, float y, float scale, glm::vec3 color);
    void setFontSize(unsigned int size);

private:
    void updateProjection();
    void loadFont();

    unsigned int mVAO;
    unsigned int mVBO;
    GLFWwindow *mWindow;
    WindowSize mWindowSize;

    std::string mFont;
    unsigned int mFontSize;
    std::map<char, FontChar> mFontChars;
    Shader *mShader;

    FT_Library mFTLibrary;
    FT_Face mFTFace;
};


#endif // RENDERTEXT_H
