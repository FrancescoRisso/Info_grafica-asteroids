#version 330 core
out vec4 FragColor;
  
uniform sampler2D texture;
in vec2 TextureCoordinates;

void main()
{
    FragColor = texture(texture, TextureCoordinates);
}
