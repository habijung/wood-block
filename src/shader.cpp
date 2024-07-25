//
// Created by habi on 7/15/2024.
//

// Class header
#include "shader.h"

// STD
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

// External
#include <glad/gl.h>


Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    /* Get shader source code */
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::string vShaderString;
    std::string fShaderString;
    const char *vShaderSource;
    const char *fShaderSource;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    /* Get code with file */
    try
    {
        std::stringstream vShaderStream, fShaderStream;

        vShaderFile.open(std::filesystem::path(vertexPath));
        vShaderStream << vShaderFile.rdbuf();
        vShaderFile.close();
        vShaderString = vShaderStream.str();
        vShaderSource = vShaderString.c_str();

        fShaderFile.open(std::filesystem::path(fragmentPath));
        fShaderStream << fShaderFile.rdbuf();
        fShaderFile.close();
        fShaderString = fShaderStream.str();
        fShaderSource = fShaderString.c_str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    /* Link and Compile vertex, fragment shader */
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderSource, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderSource, nullptr);
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

void Shader::checkCompileErrors(const unsigned int shader, const std::string &type)
{
    int success;
    char infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
}
