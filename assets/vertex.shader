#version 330 core

layout(location = 0) in vec2 position;

uniform mat4 transformMatrix;

void main()
{
    gl_Position = transformMatrix * vec4(position, 1.0, 1.0);
}