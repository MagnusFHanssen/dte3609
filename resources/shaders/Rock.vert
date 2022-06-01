#version 460 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 Normal;
out vec3 LightPos;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
//uniform vec3 camPos;

void main()
{
    FragPos = vec3(view * model * vec4(aPosition, 1.0f));
    Normal = mat3(transpose(inverse(view * model))) * aNormal;
    LightPos = vec3(view * vec4(lightPos, 1.0f));

    TexCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(aPosition, 1.0f);
}
