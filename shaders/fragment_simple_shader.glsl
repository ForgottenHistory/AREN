#version 330 core
out vec4 FragColor;

uniform vec3 u_DiffuseColor;
uniform vec3 u_SpecularColor;
uniform float u_Shininess;

void main()
{
    // Use the diffuse color for now
    FragColor = vec4(u_DiffuseColor, 1.0);
}