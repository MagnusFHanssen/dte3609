#version 330 core

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
    vec3 texColor = vec3(texture(Texture1, TexCoord));
    // We assume the light is perfectly white
    float ambient = 0.1f;
    // using normal map
    vec3 norm = normalize(vec3(texture(Texture2, TexCoord2)) + Normal);

    vec3 lightDir = normalize(LightPos - FragPos);
    float diffuse = 0.9 * max(dot(norm, lightDir), 0);

    vec3 result = texColor * (ambient + diffuse);

    fragColor = vec4(result, 1.0f);
}
