R""(
#version 410 core

#define MAX_NUMBER_OF_POINT_LIGHTS 5

out vec4 color;

in vec2 outTexCoords;
in vec3 outNormal;
in vec3 outFragPos;

struct Material
{
    sampler2D diffuseTexture1;
    sampler2D diffuseTexture2;
    sampler2D specularTexture1;
    sampler2D specularTexture2;

    float shininess;
};

struct DirectionalLight
{
    vec3 direction;

    vec3 color;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    vec3 color;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPosition;
uniform Material material;
uniform DirectionalLight directionalLight;
uniform int numberOfPointLights;
uniform PointLight pointLights[MAX_NUMBER_OF_POINT_LIGHTS];

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragmentPosition, vec3 viewDirection);



void main(void)
{
    vec3 norm = normalize(outNormal);
    vec3 viewDirection = normalize(viewPosition - outFragPos);

    vec3 result = CalculateDirectionalLight(directionalLight, norm, viewDirection);
    for(int i = 0; i < numberOfPointLights; i++)
        result += CalculatePointLight(pointLights[i], norm, outFragPos, viewDirection);

    color = vec4(outNormal, 1.0);
}


vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
    vec3 lightDirection = normalize(-light.direction);

    float diff = max(dot(normal, lightDirection), 0.0);

    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture1, outTexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseTexture1, outTexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specularTexture1, outTexCoords));

    return (ambient + diffuse + specular) * light.color;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragmentPosition, vec3 viewDirection)
{
    vec3 lightDirection = normalize(light.position - fragmentPosition);

    float diff = max(dot(normal, lightDirection), 0.0);

    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);

    float distance = length(light.position - fragmentPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                        light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture1, outTexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseTexture1, outTexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specularTexture1, outTexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular) * light.color;                    
}

)""
