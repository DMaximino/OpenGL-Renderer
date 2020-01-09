#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;
out vec3 fragmentColor;

void main()
{
    gl_Position = vec4(position, 1);
    fragmentColor = vertexColor;
};

#shader fragment
#version 330 core

in vec3 fragmentColor;
out vec3 color;

void main()
{

    color = fragmentColor;
};