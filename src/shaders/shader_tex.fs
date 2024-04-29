#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture1;
uniform float mixValue;

void main()
{
    FragColor = mix(texture(ourTexture, vec2(1.0 - TexCoord.x, TexCoord.y)), texture(ourTexture1, TexCoord), mixValue);
} 

