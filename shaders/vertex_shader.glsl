#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; // Add normal attribute

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;   // Output world position
out vec3 Normal;    // Output normal

void main()
{
    vec4 worldPos = model * vec4(aPos, 1.0);
    gl_Position = projection * view * worldPos;

    FragPos = worldPos.xyz;            // Pass world position to fragment shader
    Normal = mat3(transpose(inverse(model))) * aNormal; // Pass normal to fragment shader
}
