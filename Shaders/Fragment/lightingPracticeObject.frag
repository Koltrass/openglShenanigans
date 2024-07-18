#version 330 core
struct Material
{
	sampler2D diffuse;
	sampler2D specular;

	float shininess;
};
struct Spotlight
{
	vec3 direction;
	vec3 position;
	float cutoff;
	float outerCutoff;

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

uniform vec3 viewerPos;
uniform Material material;
uniform Spotlight lightSource;

out vec4 finalColor;

vec3 calculateSpotlight(Spotlight spotlight, vec3 norm, vec3 objectToLight);

void main()
{
	vec3 norm = normalize(normal);
	vec3 objectToLight = normalize(lightSource.position - worldPos);

	vec3 result = calculateSpotlight(lightSource, norm, objectToLight);

	finalColor = vec4(result, 1.0);
}
vec3 calculateSpotlight(Spotlight spotlight, vec3 norm, vec3 objectToLight)
{
	vec3 ambient = spotlight.ambient * vec3(texture(material.diffuse, texCoords));

	float diffuseCoef = max(dot(norm, objectToLight), 0.0);
	vec3 diffuse = diffuseCoef * lightSource.diffuse * vec3(texture(material.diffuse, texCoords));
	
	vec3 viewDir = normalize(viewerPos - worldPos);
	vec3 reflectDir = reflect(-objectToLight, norm);
	float specCoef = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = specCoef * lightSource.specular * (vec3(texture(material.specular, texCoords)));

	float theta = dot(-spotlight.direction, objectToLight);
	float epsilon = spotlight.cutoff - spotlight.outerCutoff;
	float intensity = clamp((theta-spotlight.outerCutoff)/epsilon, 0.0, 1.0);

	diffuse *= intensity;
	specular *= intensity;

	float dist = length(spotlight.position - worldPos);
	float attenuation = 1.0 / (spotlight.constant + spotlight.linear * dist + spotlight.quadratic*dist*dist);

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return ambient + diffuse + specular;
}