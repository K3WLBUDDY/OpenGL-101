#version 330 core

out vec4 color;
in vec3 Dcolor;
in vec2 TexCoord;

uniform sampler2D tex;

void main()
{
	color = texture(tex, TexCoord);
}
