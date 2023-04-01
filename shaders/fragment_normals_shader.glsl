#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 u_DiffuseColor;
uniform vec3 u_SpecularColor;
uniform float u_Shininess;

void main()
{
    // Visualize normals
    FragColor = vec4((Normal + vec3(1.0)) / 2.0, 1.0);
}