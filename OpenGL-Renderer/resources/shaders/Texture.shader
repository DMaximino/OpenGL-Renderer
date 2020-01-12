#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position, 1);
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

in vec2 v_TexCoord;
out vec4 color;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;

};