#version 330 core
out vec4 FragColor;
  
uniform sampler2D texture;
in vec2 TextureCoordinates;

void main()
{
	vec4 color = texture2D(texture, TextureCoordinates);
	if (color.w > 0) FragColor = color;
	else discard;
}
