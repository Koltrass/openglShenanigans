#version 330 core
out vec4 FragColor;
uniform vec2 changingColor;
void main()
{
	FragColor = vec4(changingColor, 0.1f, 1.0f);
}