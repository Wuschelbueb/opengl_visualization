#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float centerU;
uniform float centerV;
uniform mat2 shearMatrix;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    // skew texture coordinates
    vec2 centeredTexCoord = vec2(aTexCoords.x - centerU, aTexCoords.y - centerV);
    vec2 shearedTexCoord = shearMatrix * centeredTexCoord;
    TexCoord = shearedTexCoord + vec2(centerU, centerV);
    gl_Position = projection * view * model * vec4(FragPos, 1.0f);
}