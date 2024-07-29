#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glm/glm.hpp>


class Shader
{
public:
    Shader(const char *vertex_path, const char *fragment_path);
    ~Shader();

    void use() const;

    unsigned int getID() const;

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    static void checkCompileErrors(unsigned int shader, const std::string &type);

    unsigned int mID;
};


#endif // SHADER_H
