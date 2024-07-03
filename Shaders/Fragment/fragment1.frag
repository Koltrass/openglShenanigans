#version 330 core
in float blue;
out vec4 FragColor;
void main()
{
	FragColor = vec4(0.6f, 0.5f, blue, 1.0f);
}