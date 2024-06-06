#version 330 core

in vec3 vertexPosition;
in vec3 vertexNormal;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProjection;

out vec3 FragPos;
out vec3 Normal;

void main() {
    FragPos = vec3(matModel * vec4(vertexPosition, 1.0));
    Normal = mat3(transpose(inverse(matModel))) * vertexNormal;

    gl_Position = matProjection * matView * vec4(FragPos, 1.0);
}