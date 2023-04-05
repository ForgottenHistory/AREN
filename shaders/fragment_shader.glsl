#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 u_DiffuseColor;
uniform vec3 u_SpecularColor;
uniform float u_Shininess;

struct SunLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform SunLight u_Sun;
uniform sampler2D u_Texture;
uniform vec3 u_ViewPos;

void main()
{
    // Sample texture
    vec3 textureColor = texture(u_Texture, TexCoords).rgb;

    // Normalize the input normal
    vec3 norm = normalize(Normal);

    // Calculate ambient lighting
    vec3 ambient = u_Sun.ambient * u_DiffuseColor * textureColor;

    // Calculate the normalized direction of the light source
    vec3 lightDir = normalize(u_Sun.position - FragPos);

    // Calculate diffuse lighting
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_Sun.diffuse * (diff * u_DiffuseColor) * (diff * textureColor);

    // Calculate specular lighting
    vec3 viewDir = normalize(u_ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shininess);
    vec3 specular = u_Sun.specular * (spec * u_SpecularColor);

    // Adjust the specular calculation
    if (diff <= 0.0)
        specular = vec3(0.0, 0.0, 0.0);

    // Combine all lighting components
    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}
