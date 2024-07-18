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
	float innerCutoff;
	float outerCutoff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct DirectionLight
{
	vec3 direction;

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

vec3 calculateSpotlight(Spotlight light, vec3 norm, vec3 viewDirection,vec3 objectToLight);
vec3 calculateDirectionLight(DirectionLight light, vec3 norm, vec3 viewDirection);

void main()
{
	vec3 norm = normalize(normal);
	vec3 viewDirection = normalize(viewerPos - worldPos);
	vec3 objectToLight = normalize(lightSource.position - worldPos);

	vec3 result = calculateSpotlight(lightSource, norm, viewDirection,objectToLight);

	finalColor = vec4(result, 1.0);
}

vec3 calculateSpotlight(Spotlight light, vec3 norm, vec3 viewDirection,vec3 objectToLight)
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

	float diffuseCoef = max(dot(norm, objectToLight), 0.0);
	vec3 diffuse = diffuseCoef * light.diffuse * vec3(texture(material.diffuse, texCoords));
	
	vec3 reflectDir = reflect(-objectToLight, norm);
	float specCoef = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);
	vec3 specular = specCoef * light.specular * (vec3(texture(material.specular, texCoords)));

	float theta = dot(-light.direction, objectToLight);
	float epsilon = light.innerCutoff - light.outerCutoff;
	float intensity = clamp((theta-light.outerCutoff)/epsilon, 0.0, 1.0);

	diffuse *= intensity;
	specular *= intensity;

	float dist = length(light.position - worldPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic*dist*dist);

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}
vec3 calculateDirectionLight(DirectionLight light, vec3 norm, vec3 viewDirection)
{
	vec3 lightDirection = normalize(light.direction);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

	float diffuseCoef = max(dot(-lightDirection, norm), 0.0);
	vec3 diffuse = diffuseCoef * light.diffuse * vec3(texture(material.diffuse, texCoords));

	vec3 reflectDirection = reflect(-lightDirection, norm);
	float specCoef = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = specCoef * light.specular * (vec3(texture(material.specular, texCoords)));

	return (ambient + diffuse + specular);
}