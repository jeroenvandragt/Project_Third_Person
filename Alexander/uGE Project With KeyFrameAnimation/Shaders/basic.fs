#version 430
//#extension GL_ARB_explicit_uniform_location : require


                            //uniform float time;


uniform vec3 cameraDirection;
uniform	mat4 model;
uniform sampler2D colorMap;
uniform vec3 light; // point light in world

in vec2 fragTexCoord; // uv
in vec3 fragNormal;   // normal
in vec3 fragVert;     // vertex

out vec4 finalColor; // to screenbuffer

void main() {
    // set basic values for the light;
    vec3 lightPos = light;
    vec3 intensities = vec3 ( 1.0f ,1.0f ,1.0f ); // light Color chris, ambientColor
    float lightAttenuation = 0.1f; //Attenuation is the loss of light intensity over distance. The greater the distance, the lower the intensity. (0,2 = 20% light recieved on an object) // chris, intensity
    float ambientCoefficient = 0.005f; // overall lighting on the scene (there will be light, always, everywhere)
    vec3 materialSpecularColor = vec3 ( 1.0f ,1.0f ,1.0f ); // material color reflection
    float materialShininess = 80.0f;

    // normal moet worden wNormal
    vec3 normal = normalize(transpose(inverse(mat3(model))) * fragNormal);
    vec3 surfacePos = vec3(model * vec4(fragVert, 1));
    vec4 surfaceColor = texture(colorMap, fragTexCoord);
    vec3 surfaceToLight = normalize(lightPos - surfacePos);
    vec3 surfaceToCamera = normalize(cameraDirection - surfacePos);

    //ambient
    vec3 ambient = ambientCoefficient * surfaceColor.rgb * intensities;

    //diffuse
    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
    vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * intensities;

    //specular
    float specularCoefficient = 0.0;
    if(diffuseCoefficient > 0.0)
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), materialShininess);
    vec3 specular = specularCoefficient * materialSpecularColor * intensities;

    //attenuation
    float distanceToLight = length(lightPos - surfacePos);
    float attenuation = 1.0 / (1.0 + lightAttenuation * pow(distanceToLight, 2));

    //linear color (color before gamma correction)
    vec3 linearColor = ambient + attenuation *(diffuse + specular);

    //final color (after gamma correction)
    vec3 gamma = vec3(1.0/2.2);
    finalColor = vec4(pow(linearColor, gamma), surfaceColor.a);
    //finalColor = vec4(linearColor, surfaceColor.a); // enable this to negate gamma correction
}
