#version 330 core

out vec4 FragColor;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_ViewPosition;

uniform float u_SpecExponent;
in vec3 FragPos;
in vec3 Normal;

void main()
{
    float ambient = 0.1; // Ambient lighting strength

    vec3 normal = normalize(Normal);                                  // Normalizes the ... normal vector
    vec3 lightDirection = normalize(u_LightPosition - FragPos);       // Calculate direction vector from surface to light source
    float diffusion = max(dot(normal, lightDirection), 0.0);          // Calculate the intnsity of diffusion by taking the dot product between the normal, and the light direction

    vec3 viewDirection = normalize(u_ViewPosition - FragPos);         // Calculate the direction vector pointing from surface of object to the camera
    vec3 reflectDirection = reflect(-lightDirection, normal);         // Calculate the reflected direction vector pointing from the surface to outside

    float spec = pow(max(dot(reflectDirection, viewDirection), 0.0f), u_SpecExponent);  // Specular lighting formula (Spec exponent increases intensity)
    
    float specularIntensity = 0.5f; // Specular strength factor

    float specular = spec * specularIntensity;  // Calculate overall spec value by multiplying intensity and strenght

    
    vec3 result = ( ambient + diffusion + specular ) * u_ObjectColor * u_LightColor; // Resulting ambient diffusion and specular values multiplied to the object

    
    FragColor = vec4(result, 1.0f);
    
}