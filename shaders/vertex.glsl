#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float g_uOffset;
uniform mat4 model;
uniform mat4 perspective;
uniform mat4 view;

out vec3 ourColor;
    
void main()
{
    ourColor = aColor;
    gl_Position =  perspective * view *  model * vec4(aPos, 1.0);
}