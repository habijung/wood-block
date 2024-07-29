#include "Shader.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/gl.h>


Shader::Shader(const char *vertex_path, const char *fragment_path)
{
    /* Get shader source code */
    std::ifstream v_shader_file;
    std::ifstream f_shader_file;
    std::string v_shader_string;
    std::string f_shader_string;
    const char *v_shader_source;
    const char *f_shader_source;

    v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    /* Get code with file */
    try
    {
        std::stringstream v_shader_stream;
        std::stringstream f_shader_stream;

        v_shader_file.open(std::filesystem::path(vertex_path));
        v_shader_stream << v_shader_file.rdbuf();
        v_shader_file.close();
        v_shader_string = v_shader_stream.str();
        v_shader_source = v_shader_string.c_str();

        f_shader_file.open(std::filesystem::path(fragment_path));
        f_shader_stream << f_shader_file.rdbuf();
        f_shader_file.close();
        f_shader_string = f_shader_stream.str();
        f_shader_source = f_shader_string.c_str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    /* Link and Compile vertex, fragment shader */
    unsigned int vertex, fragment;
    int success;
    char info_log[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_shader_source, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_shader_source, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    checkCompileErrors(fragment, "FRAGMENT");

    /* Link and Compile shader program */
    mID = glCreateProgram();
    glAttachShader(mID, vertex);
    glAttachShader(mID, fragment);
    glLinkProgram(mID);
    glGetProgramiv(mID, GL_LINK_STATUS, &success);
    checkCompileErrors(mID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() { glDeleteProgram(mID); }

void Shader::use() const { glUseProgram(mID); }

unsigned int Shader::getID() const { return mID; }

void Shader::setBool(const std::string &name, const bool value) const
{
    glUniform1i(glGetUniformLocation(mID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string &name, const int value) const
{
    glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, const float value) const
{
    glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompileErrors(const unsigned int shader, const std::string &type)
{
    int success;
    char info_log[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, info_log);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << info_log << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, info_log);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << info_log << std::endl;
        }
    }
}
