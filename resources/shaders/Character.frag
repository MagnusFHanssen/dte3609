#version 460 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 LightPos;
in vec3 FragPos;


out vec4 fragColor;

uniform sampler2D Texture1;
uniform vec3 lightColor;

void main(void)
{
    vec3 texColor = texture(Texture1, TexCoord).rgb;
    vec3 ambient = 0.1f * lightColor;

    vec3 norm = normalize(Normal);

    vec3 lightDir = normalize(LightPos - FragPos);
    vec3 diffuse = max(dot(norm, lightDir), 0) * lightColor;

    vec3 viewDir = normalize(-FragPos);
    vec3 refDir = reflect(-lightDir, norm);
    vec3 specular = 0.3 * pow(max(dot(viewDir, refDir), 0.0), 32) * lightColor;

    vec3 result = (ambient + diffuse) * texColor;

    fragColor = vec4(result, 1.0);
}
