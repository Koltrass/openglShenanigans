#version 330 core
struct Material
{
	sampler2D diffuse;
	sampler2D specular;

	float shininess;
};
struct LightSource
{
	vec3 direction;
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 normal;
in vec3 worldPos;
in vec2 texCoords;

uniform vec3 viewPos;
uniform Material material;
uniform LightSource lightSource;

out vec4 finalColor;

void main()
{
	float dist = length(lightSource.position - worldPos);
	float attenuation = 1.0 / (lightSource.constant + lightSource.linear * dist + lightSource.quadratic*dist*dist);

	vec3 ambient = lightSource.ambient * vec3(texture(material.diffuse, texCoords));

	vec3 norm = normalize(normal);
	vec3 objectToLight = normalize(lightSource.position - worldPos);
	float diffuseCoef = max(dot(norm, objectToLight), 0.0);
	vec3 diffuse = diffuseCoef * lightSource.diffuse * vec3(texture(material.diffuse, texCoords));

	vec3 viewDir = normalize(viewPos - worldPos);
	vec3 reflectDir = reflect(-objectToLight, norm);
	float specCoef = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = specCoef * lightSource.specular * (vec3(texture(material.specular, texCoords)));

	vec3 result = (ambient+diffuse+specular)*attenuation;
	finalColor = vec4(result, 1.0);
}