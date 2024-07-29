#include <filesystem>
#include <iostream>
#include <sstream>

#include <glad/gl.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera/Camera.h"
#include "render/RenderText.h"
#include "shader/Shader.h"


/* GLFW callback function */
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void cursor_position_callback(GLFWwindow *window, double pos_x, double pos_y);
void scroll_callback(GLFWwindow *window, double offset_x, double offset_y);

void processInput(GLFWwindow *window);

struct CursorPos
{
    float x;
    float y;
};

constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

CursorPos CursorPos = {0.0f, 0.0f};
Camera Camera(glm::vec3(0.0f, 0.0f, 3.0f));

float obj[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
unsigned int indices[] = {0, 1, 2};

float delta_time = 0.0f;
float last_frame = 0.0f;


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
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;

        return -1;
    }

    /* Set class RenderText */
    RenderText RenderText(window, "glsl/font.vert", "glsl/font.frag");

    /* Shader: Object */
    Shader ObjectShader("glsl/obj.vert", "glsl/obj.frag");

    /* Set up vertex data and buffer */
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(obj), obj, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);

    /* Render loop */
    while (!glfwWindowShouldClose(window))
    {
        float current_frame = static_cast<float>(glfwGetTime());
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        processInput(window);

        // Rendering
        glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Draw objects */
        ObjectShader.use();

        glm::mat4 model = glm::rotate(glm::mat4(1.0f), static_cast<float>(glfwGetTime()) * glm::radians(-55.0f),
                                      glm::vec3(1.0f, 0.0f, 0.0f));
        ObjectShader.setMat4("model", model);

        glm::mat4 view = Camera.getViewMatrix();
        ObjectShader.setMat4("view", view);

        glm::mat4 projection =
            glm::perspective(glm::radians(Camera.getZoom()),
                             static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
        ObjectShader.setMat4("projection", projection);

        glBindVertexArray(vao);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Draw mouse cursor position text */
        std::stringstream cursor_pos_text;
        cursor_pos_text << "x: " << static_cast<int>(CursorPos.x) << ", y: " << static_cast<int>(CursorPos.y);
        RenderText.renderText(cursor_pos_text.str(), CursorPos.x, CursorPos.y, 1.0f, glm::vec3(0.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }

void cursor_position_callback(GLFWwindow *window, double pos_x, double pos_y)
{
    glfwGetCursorPos(window, &pos_x, &pos_y);
    CursorPos.x = static_cast<float>(pos_x);
    CursorPos.y = static_cast<float>(pos_y);
}

void scroll_callback(GLFWwindow *window, double offset_x, double offset_y)
{
    Camera.processMouseScroll(static_cast<float>(offset_y));
}

void processInput(GLFWwindow *window)
{
    /* Exit */
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    /* Camera Move */
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Camera.processKeyboard(FORWARD, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Camera.processKeyboard(BACKWARD, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Camera.processKeyboard(LEFT, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Camera.processKeyboard(RIGHT, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        Camera.processKeyboard(UP, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        Camera.processKeyboard(DOWN, delta_time);
    }
}
