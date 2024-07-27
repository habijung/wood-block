#include <filesystem>
#include <iostream>

#include <glad/gl.h>

#include "RenderText.h"

RenderText::RenderText(GLFWwindow *window, const char *vertex_path, const char *fragment_path,
                       const unsigned int font_size)
{
    mVAO = 0;
    mVBO = 0;
    mFont = std::filesystem::path("data/fonts/arial.ttf").string();
    mFontSize = font_size;
    mShader = new Shader(vertex_path, fragment_path);
    mWindow = window;

    updateProjection();
    loadFont();

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

RenderText::~RenderText() { delete mShader; };

void RenderText::renderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    updateProjection();

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    mShader->use();
    glUniform3f(glGetUniformLocation(mShader->getID(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(mVAO);

    std::string::const_iterator iter;

    for (iter = text.begin(); iter != text.end(); iter++)
    {
        FontChar ch = mFontChars[*iter];

        float xpos = x + ch.bearing.x * scale;
        float ypos = (static_cast<float>(mWindowSize.height) - y) - (ch.size.y - ch.bearing.y) * scale;
        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        // Update VBO for each character
        float vertices[6][4] = {{xpos, ypos + h, 0.0f, 0.0f}, {xpos, ypos, 0.0f, 1.0f},
                                {xpos + w, ypos, 1.0f, 1.0f}, {xpos, ypos + h, 0.0f, 0.0f},
                                {xpos + w, ypos, 1.0f, 1.0f}, {xpos + w, ypos + h, 1.0f, 0.0f}};

        glBindTexture(GL_TEXTURE_2D, ch.texture_id);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Render Quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += static_cast<float>(ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
}

void RenderText::setFontSize(unsigned int size)
{
    // TODO: Update font size
    mFontSize = size;
    loadFont();
}

void RenderText::updateProjection()
{
    glfwGetWindowSize(mWindow, &mWindowSize.width, &mWindowSize.height);

    mShader->use();
    glm::mat4 projection =
        glm::ortho(0.0f, static_cast<float>(mWindowSize.width), 0.0f, static_cast<float>(mWindowSize.height));
    glUniformMatrix4fv(glGetUniformLocation(mShader->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void RenderText::loadFont()
{
    if (mFont.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    if (FT_Init_FreeType(&mFTLibrary))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    if (FT_New_Face(mFTLibrary, mFont.c_str(), 0, &mFTFace))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(mFTFace, 0, mFontSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char ch = 0; ch < 128; ch++)
    {
        if (FT_Load_Char(mFTFace, ch, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }

        unsigned int texture;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, mFTFace->glyph->bitmap.width, mFTFace->glyph->bitmap.rows, 0, GL_RED,
                     GL_UNSIGNED_BYTE, mFTFace->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        FontChar fontChar = {texture, glm::fvec2(mFTFace->glyph->bitmap.width, mFTFace->glyph->bitmap.rows),
                             glm::fvec2(mFTFace->glyph->bitmap_left, mFTFace->glyph->bitmap_top),
                             static_cast<unsigned int>(mFTFace->glyph->advance.x)};

        mFontChars.insert(std::pair<char, FontChar>(ch, fontChar));
    }

    FT_Done_Face(mFTFace);
    FT_Done_FreeType(mFTLibrary);
}
