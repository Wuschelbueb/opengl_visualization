#version 330 core
out vec4 FragColor;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoord;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct Light {
    //vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform vec3 objectColor;
uniform Material material;
uniform Light light;

// texture samplers
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;

// // Coordinates to start the repetition from
uniform float center_u;
uniform float center_v;

uniform bool changeTexture;

// // Set scale for uv coordinates
uniform float scale;

// Number of elements along each axis
uniform int elements;

uniform float u_angle;

void main()
{ 
    vec2 center = vec2(center_u, center_v);
    vec2 scale = vec2(scale, scale);
    float sin_factor = sin(u_angle);
    float cos_factor = cos(u_angle);
    vec2 bounds = vec2(float(elements/2), float(elements/2));

    //  Compute absolute offset from center
    vec2 offset = scale * (TexCoord - center);

    // ambient
    vec3 ambient = light.ambient * light.diffuse; // * texture(material.diffuse, TexCoord).rgb; 
        
    // diffuse 
    vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(light.position - FragPos);
    vec3 lightDir = normalize(-light.direction);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff; // * texture(material.diffuse, TexCoord).rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec; // * texture(material.specular, TexCoord).rgb;

    // Do texture lookup based on the vertices texture coordinates
    // color of U coord
    float texCoordX = TexCoord.x;
    float texCoordY = TexCoord.y;
    float tempX = texCoordX - int(texCoordX);
    float tempY = texCoordY - int(texCoordY);
    int fracPartX = int(tempX*10);
    int fracPartY = int(tempY*10);

    vec3 tempLighting = (ambient + diffuse + specular);
    vec4 quad_texture;
    if(changeTexture) {
        quad_texture = texture(texture_diffuse1, offset);    
    } else {
        quad_texture = texture(texture_diffuse2, offset);
    }
    vec4 bgColorEnd = vec4(tempLighting * objectColor, 1.0);
    vec4 quadTexEnd = vec4(tempLighting, 1.0) * quad_texture;

    if (all(lessThan(abs(offset), bounds))) {
        FragColor = mix(bgColorEnd,quadTexEnd, 1);
    }else {
        FragColor = bgColorEnd;
    }
    if (isnan(TexCoord.x) || isnan(TexCoord.y)) {
        FragColor = bgColorEnd;
    }
}