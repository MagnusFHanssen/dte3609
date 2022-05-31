#version 460 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexture;
layout(location = 3) in vec2 aTexture2;

out vec2 TexCoord;
out vec2 TexCoord2;
out vec3 Normal;
out vec3 LightPos;
out vec3 FragPos;

uniform vec3 lightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(view * model * vec4(aPosition, 1.0));
    Normal = mat3(transpose(inverse(view * model))) * aNormal;
    LightPos = vec3(view * vec4(lightPos, 1.0));

    gl_Position = projection * view  * model * vec4(aPosition, 1.0f);

    TexCoord = aTexture;
    TexCoord2 = aTexture2;
}
