#version 330 core
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
struct LightSource
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 normal;
in vec3 worldPos;

uniform vec3 viewPos;
uniform Material material;
uniform LightSource lightSource;

out vec4 finalColor;

void main()
{
	vec3 ambient = material.ambient * lightSource.ambient;

	vec3 norm = normalize(normal);
	vec3 objectToLight = normalize(lightSource.position - worldPos);
	float diffuseCoef = max(dot(norm, objectToLight), 0.0);
	vec3 diffuse = diffuseCoef * material.diffuse * lightSource.diffuse;

	vec3 viewDir = normalize(viewPos - worldPos);
	vec3 reflectDir = reflect(-objectToLight, norm);
	float specCoef = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = material.specular * specCoef * lightSource.specular;

	vec3 result = ambient+diffuse+specular;
	finalColor = vec4(result, 1.0);
}