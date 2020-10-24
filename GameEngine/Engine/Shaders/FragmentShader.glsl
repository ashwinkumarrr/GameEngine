#version 450 core

struct Light
{
	vec3 lightPos;
	float ambientValue;
	float diffuseValue;
	vec3 color;
};

in vec3 Normal;
in vec2 Texcoords;
in vec3 Colour;
in vec3 FragPosition;

out vec4 fColour;

uniform sampler2D inputTexture;
uniform Light light;
uniform vec3 cameraPos;

void main()
{
	vec3 ambient = light.ambientValue * texture(inputTexture, Texcoords).rgb * light.color;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * texture(inputTexture, Texcoords).rgb * light.color;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(cameraPos - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * light.color;


	vec3 result = ambient + diffuse + specular;

	fColour = vec4(result, 1.0f);
}