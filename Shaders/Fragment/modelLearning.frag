#version 330 core
struct Material
{
	sampler2D diffuse0;
	sampler2D specular0;

	float shininess;
};
struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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

#define NR_POINT_LIGHTS 2
uniform PointLight pointLights[NR_POINT_LIGHTS];

#define NR_SPOTLIGHTS 1
uniform Spotlight spotlights[NR_SPOTLIGHTS];

uniform DirectionLight directionLight;

out vec4 finalColor;

vec3 calculatePointLight(PointLight light, vec3 norm, vec3 viewDirection, vec3 objectToLight);
vec3 calculateSpotlight(Spotlight light, vec3 norm, vec3 viewDirection,vec3 objectToLight);
vec3 calculateDirectionLight(DirectionLight light, vec3 norm, vec3 viewDirection);

void main()
{
	vec3 norm = normalize(normal);
	vec3 viewDirection = normalize(viewerPos - worldPos);

	vec3 result = calculateDirectionLight(directionLight, norm, viewDirection);

	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		vec3 objectToPointLight = normalize(pointLights[i].position - worldPos);
		result += calculatePointLight(pointLights[i], norm, viewDirection, objectToPointLight);
	}
	for (int i = 0; i < NR_SPOTLIGHTS; i++)
	{
		vec3 objectToSpotlight = normalize(spotlights[i].position - worldPos);
		result += calculateSpotlight(spotlights[i], norm, viewDirection,objectToSpotlight);
	}

	finalColor = vec4(result, 1.0);
}

vec3 calculatePointLight(PointLight light, vec3 norm, vec3 viewDirection, vec3 objectToLight)
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse0, texCoords));

	float diffuseCoef = max(dot(norm, objectToLight), 0.0);
	vec3 diffuse = diffuseCoef * light.diffuse * vec3(texture(material.diffuse0, texCoords));

	vec3 reflectDir = reflect(-objectToLight, norm);
	float specCoef = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);
	vec3 specular = specCoef * light.specular * (vec3(texture(material.specular0, texCoords)));

	float dist = length(light.position - worldPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic*dist*dist);

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);	
}
vec3 calculateSpotlight(Spotlight light, vec3 norm, vec3 viewDirection,vec3 objectToLight)
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse0, texCoords));

	float diffuseCoef = max(dot(norm, objectToLight), 0.0);
	vec3 diffuse = diffuseCoef * light.diffuse * vec3(texture(material.diffuse0, texCoords));
	
	vec3 reflectDir = reflect(-objectToLight, norm);
	float specCoef = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);
	vec3 specular = specCoef * light.specular * (vec3(texture(material.specular0, texCoords)));

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

	vec3 ambient = light.ambient * vec3(texture(material.diffuse0, texCoords));

	float diffuseCoef = max(dot(-lightDirection, norm), 0.0);
	vec3 diffuse = diffuseCoef * light.diffuse * vec3(texture(material.diffuse0, texCoords));

	vec3 reflectDirection = reflect(-lightDirection, norm);
	float specCoef = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = specCoef * light.specular * (vec3(texture(material.specular0, texCoords)));

	return (ambient + diffuse + specular);
}
