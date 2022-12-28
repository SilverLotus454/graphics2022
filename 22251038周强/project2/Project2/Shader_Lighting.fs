#version 330 core
out vec4 color;

in vec2 TexCoord;

uniform sampler2D sunTexture;

void main()
{
    vec3 sunColor = vec3(texture(sunTexture, TexCoord));

    color = vec4(sunColor, 1.0f); //������ά����������Ԫ��Ϊ 1.0f
}