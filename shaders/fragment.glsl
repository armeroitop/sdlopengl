#version 410 core
in vec3 ourColor;

uniform bool useOverrideColor;
uniform vec3 overrideColor;

out vec4 FragColor;
void main()
{
    vec3 color = useOverrideColor
        ? overrideColor
        : ourColor;

    FragColor = vec4(color, 1.0);
}