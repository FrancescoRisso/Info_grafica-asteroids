#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

void main()
{    
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(vec3(0, 0, -0.75) - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 color = 1.15* diff * vec3(1);

    FragColor = vec4(color, 1.0);
}
