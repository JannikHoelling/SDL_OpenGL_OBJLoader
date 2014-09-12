#version 330

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

//layout(location = 0)  in Particle particle;
layout(location = 0)  in vec3 position;
layout(location = 1)  in vec2 texcoord;

//out vec4 color;
out vec2 f_texcoord;

void main()
{
	//color = normalize(velocity);
    gl_Position = projectionMatrix * viewMatrix * vec4(position,1);
    f_texcoord = texcoord;
}
