#version 330 core
out vec4 FragColor;

in vec3 fragCol;
in vec2 texCoord;

uniform sampler2D myTexture1;
uniform sampler2D myTexture2;
uniform float mixVal;

void main()
{
	FragColor = mix(texture(myTexture1, texCoord), texture(myTexture2, vec2(-texCoord.s, texCoord.t)), mixVal) * vec4(fragCol, 1.0f);
}