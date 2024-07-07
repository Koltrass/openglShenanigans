#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTex;

out vec3 fragCol;
out vec2 texCoord;

uniform mat4 transformation;
void main()
{
	gl_Position = transformation*vec4(aPos, 1.0);
	fragCol = aCol;
	texCoord = aTex;
}