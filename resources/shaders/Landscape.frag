#version 460 core

in vec2 TexCoord;
in vec2 TexCoord2;
in vec3 Normal;
in vec3 LightPos;
in vec3 FragPos;


uniform sampler2D Texture1;
uniform sampler2D Texture2;

out vec4 fragColor;

void main(void)
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0); //Can be changed to uniform if I want to change light color
    vec3 texColor = vec3(texture(Texture1, TexCoord));
    // We assume the light is perfectly white
    vec3 ambient = 0.1f * lightColor;
    // using normal map
    vec3 norm = normalize(vec3(texture(Texture2, TexCoord2))/* + Normal*/);

    vec3 lightDir = normalize(LightPos - FragPos);
    vec3 diffuse = max(dot(norm, lightDir), 0) * lightColor;


    vec3 viewDir = normalize(-FragPos);
    vec3 refDir = reflect(-lightDir, norm);
    vec3 specular = 0.5 * pow(max(dot(viewDir, refDir), 0.0), 32) * lightColor;

    vec3 result = (ambient + diffuse) * texColor + specular;

    fragColor = vec4(result, 1.0f);
}
