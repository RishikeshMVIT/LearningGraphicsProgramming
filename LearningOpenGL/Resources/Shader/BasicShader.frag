#version 330 core

in vec3 vertexColor;
in vec2 uvCoords;
in vec3 normal;
in vec3 currentPosition;

out vec4 fragColor;

uniform sampler2D diffuseTexture;
uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

void main()
{
    //Ambient
    float ambient = 0.20;

    //Diffuse
    vec3 lightDirection = normalize(lightPosition - currentPosition);
    float diffuse = max(dot(normal, lightDirection), 0.0);

    //Specular
    float specularLight = 0.50;
    vec3 viewDirection = normalize(cameraPosition - currentPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 8);
    float specular = specularAmount * specularLight;

    fragColor = texture(diffuseTexture, uvCoords) * lightColor * (diffuse + ambient + specular);
}