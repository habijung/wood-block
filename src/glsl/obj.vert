#version 410 core

layout (location = 0) in vec3 aPos; // attribute position 0

out vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexColor = aPos;
}
