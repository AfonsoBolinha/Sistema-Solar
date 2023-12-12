// Em seu vertex shader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos; // Posição do fragmento no espaço do mundo
out vec3 Normal;   // Normal do fragmento no espaço do mundo
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos; // Posição da luz no espaço do mundo
uniform vec3 viewPos;  // Posição da câmera no espaço do mundo

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aColor;
    TexCoords = aTexCoords;
}
