//
// Created by habi on 7/15/2024.
//

#ifndef SHADER_H
#define SHADER_H

// STD
#include <string>


class Shader
{
public:
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();

    void use() const;

    unsigned int getID() const;

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    static void checkCompileErrors(unsigned int shader, const std::string &type);

    unsigned int mID;
};


#endif // SHADER_H
