#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 finalColor;

uniform vec3 viewPos;
struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;
uniform vec4 objectColor;

void main() {

    vec3 ambient = light.ambient * objectColor.rgb;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * objectColor.rgb;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = light.specular * spec * objectColor.rgb;

    vec3 result = ambient + diffuse + specular;
    finalColor = vec4(result, objectColor.a);
}
