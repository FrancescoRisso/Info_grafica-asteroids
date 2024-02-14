#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

void main()
{    
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(vec3(0, 0, 1) - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 color = diff * vec3(1);

    FragColor = vec4(color, 1.0);
	// FragColor = vec4(1);
	// FragColor = vec4(0.5+0.5*Normal.y, 0, 0, 1);
}
