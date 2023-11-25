#version 410 core
out vec4 FragColor;

struct Material {
    sampler2D texture_diffuse1;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

#define MAX_DIRECTIONAL_LIGHTS 1
uniform int total_directional_lights;

#define MAX_POINT_LIGHTS 4
uniform int total_point_lights;

#define MAX_SPOT_LIGHTS 1
uniform int total_spot_lights;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLights[MAX_DIRECTIONAL_LIGHTS]; //initialize an array of the maximum size of directional lights allowed
uniform PointLight pointLights[MAX_POINT_LIGHTS]; //initialize an array of the maximum size of point lights allowed
uniform SpotLight spotLights[MAX_SPOT_LIGHTS]; //initialize an array of the maximum size of spot lights allowed
uniform Material material;

// function prototypes
vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
    vec4 result;
    for (int i = 0; i < total_directional_lights; i++) //only process as many point lights as exist in the entity system
        result = CalcDirLight(dirLights[i], norm, viewDir);
    // phase 2: point lights
    for(int i = 0; i < total_point_lights; i++) //only process as many point lights as exist in the entity system
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    // phase 3: spot light
    for (int i = 0; i < total_spot_lights; i++) //only process as many point lights as exist in the entity system
        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);    
    
    FragColor = result;
}

// calculates the color when using a directional light.
vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec4 ambient = vec4(light.ambient,1) * texture(material.texture_diffuse1, TexCoords);
    vec4 diffuse =  vec4(light.diffuse,1) * diff * texture(material.texture_diffuse1, TexCoords);
    return (ambient + diffuse);
}

// calculates the color when using a point light.
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec4 ambient = vec4(light.ambient,1) * texture(material.texture_diffuse1, TexCoords);
    vec4 diffuse = vec4(light.diffuse,1) * diff * texture(material.texture_diffuse1, TexCoords);
    ambient.xyz *= attenuation;
    diffuse.xyz *= attenuation;
    return (ambient + diffuse);
}

// calculates the color when using a spot light.
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec4 ambient = vec4(light.ambient,1) * texture(material.texture_diffuse1, TexCoords);
    vec4 diffuse = vec4(light.diffuse,1) * diff * texture(material.texture_diffuse1, TexCoords);
    ambient.xyz *= attenuation * intensity;
    diffuse.xyz *= attenuation * intensity;
    return (ambient + diffuse);
}