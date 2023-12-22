#version 330 core
out vec4 FragColor;
uniform vec3 textColor; // Color uniform

void main()
{
    FragColor = vec4(textColor, 1.0);
}