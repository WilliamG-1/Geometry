#version 330 core
struct Material{
    vec3 ambient;
    vec3 diffusion;
    vec3 specular;

    sampler2D t_diffuse;
    sampler2D t_specular;
    //sampler2D t_emmission;
    float shininess;
};
struct Light{
    vec3 position;
    
    vec3 ambient;
    vec3 diffusion;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Spotlight{
    vec3 position;
    vec3 direction;
    float cutoff;
    float outerCutoff;

    vec3 ambient;
    vec3 diffusion;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;

uniform Material u_Material;
uniform Light u_Light;
uniform Spotlight u_Spotlight;

uniform vec3 u_ViewPosition;

uniform float u_SpecExponent;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
void main()
{
    // // Attentuation 
    // float distance = length(FragPos - u_Light.position);
    // float attenuation = 1 / (u_Light.constant + u_Light.linear * distance + u_Light.quadratic * pow(distance, 2));

    // // Ambient lighting strength
    // vec3 ambient = u_Light.ambient * vec3(texture(u_Material.t_diffuse, TexCoords));   // Calculate Ambient vector;

    // // Diffusion Lighting
    // vec3 normal = normalize(Normal);                                   // Normalizes the ... normal vector
    // vec3 lightDirection = normalize(u_Light.position - FragPos);       // Calculate direction vector from surface to light source
    // float diff = max(dot(normal, lightDirection), 0.0);                // Calculate the intnsity of diffusion by taking the dot product between the normal, and the light direction
    // vec3 diffusion = u_Light.diffusion * diff * vec3(texture(u_Material.t_diffuse, TexCoords)); // Calculate Diffusion Vector

    // // Specular Lighting
    // vec3 viewDirection = normalize(u_ViewPosition - FragPos);         // Calculate the direction vector pointing from surface of object to the camera
    // vec3 reflectDirection = reflect(-lightDirection, normal);         // Calculate the reflected direction vector pointing from the surface to outside
    // float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), u_Material.shininess);  // Specular lighting formula (Spec exponent increases intensity)
    // vec3 specular = u_Light.specular * spec * vec3(texture(u_Material.t_specular, TexCoords)); // Calculate specular vector

    // // Result
    // vec3 result = ambient * 5;


    //======================== SpotLight ======================= \\
    
    // Attentuation 
    vec3 lightDirection = normalize(u_Spotlight.position - FragPos);       // Calculate direction vector from surface to light source

    float theta = dot(lightDirection, normalize(-u_Spotlight.direction));
    float epsilon = u_Spotlight.cutoff - u_Spotlight.outerCutoff;
    float coneIntensity = clamp((theta - u_Spotlight.outerCutoff)/epsilon, 0, 1) * 4;
    
    
    float distance = length(FragPos - u_Spotlight.position);
    float attenuation = 1 / (1 + u_Spotlight.linear * distance + u_Spotlight.quadratic * pow(distance, 2));

    // Ambient lighting strength
    vec3 ambient =  u_Spotlight.ambient * vec3(texture(u_Material.t_diffuse, TexCoords));   // Calculate Ambient vector;

    // Diffusion Lighting
    vec3 normal = normalize(Normal);                                   // Normalizes the ... normal vector
    
    float diff = max(dot(normal, lightDirection), 0.0);                // Calculate the intnsity of diffusion by taking the dot product between the normal, and the light direction
    vec3 diffusion = u_Spotlight.diffusion * diff * vec3(texture(u_Material.t_diffuse, TexCoords)); // Calculate Diffusion Vector

    // Specular Lighting
    vec3 viewDirection = normalize(u_ViewPosition - FragPos);         // Calculate the direction vector pointing from surface of object to the camera
    vec3 reflectDirection = reflect(-lightDirection, normal);         // Calculate the reflected direction vector pointing from the surface to outside
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), u_Material.shininess);  // Specular lighting formula (Spec exponent increases intensity)
    vec3 specular = u_Spotlight.specular * spec * vec3(texture(u_Material.t_specular, TexCoords)); // Calculate specular vector

    vec3 result = attenuation * (2 * ambient + coneIntensity * (specular + diffusion));

    FragColor = vec4(result, 1.0f);
    
}