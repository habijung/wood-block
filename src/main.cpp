#include <filesystem>
#include <iostream>
#include <sstream>

#include <glad/gl.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "render/RenderText.h"
#include "shader.h"


void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
void processInput(GLFWwindow *window);
void render_text(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color);

struct
{
    double x;
    double y;
} cursorPos;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float obj[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
unsigned int indices[] = {0, 1, 2};


int main()
{
    /* GLFW Init */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "untitled", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Faild to initialize GLAD" << std::endl;

        return -1;
    }

    /* Shader: font */
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
    RenderText renderText("glsl/font.vert", "glsl/font.frag", projection);

    /* Shader: Object */
    Shader objShader("glsl/obj.vert", "glsl/obj.frag");

    /* Set up vertex data and buffer */
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(obj), obj, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /* Render loop */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Rendering
        glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        objShader.use();

        glBindVertexArray(VAO);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        std::stringstream cursorText;
        cursorText << "x: " << cursorPos.x << ", y: " << cursorPos.y;
        renderText.render_text(cursorText.str(), static_cast<float>(cursorPos.x),
                               static_cast<float>(SCR_HEIGHT - cursorPos.y), 1.0f, glm::vec3(0.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, const int width, const int height)
{
    glViewport(0, 0, width, height);
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    glfwGetCursorPos(window, &xpos, &ypos);
    cursorPos = {xpos, ypos};

#ifdef SHOW_COUT
    std::cout << "x: " << cursorPos.x << ", y: " << cursorPos.y << std::endl;
#endif
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
