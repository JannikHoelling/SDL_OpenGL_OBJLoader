#version 330

//in vec4 color;
in vec2 f_texcoord;
out vec4 outColor;

uniform sampler2D texture;

void main() {
    vec2 flipped_texcoord = vec2(f_texcoord.x, 1.0 - f_texcoord.y);
    outColor = texture2D(texture, flipped_texcoord);
	//outColor = texture2D(texture, f_texcoord);
	//outColor = vec4( 1.0, 1.0, 1.0, 1.0);
	//outColor = color;
}
