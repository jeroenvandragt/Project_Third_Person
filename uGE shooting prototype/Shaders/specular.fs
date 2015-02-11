#version 330

uniform sampler2D colorMap;
uniform vec3 cameraPosition;
uniform vec3 light;

in vec2 texCoord;

//in float diffuse;

//in vec3 lightDir;
in vec4 wNormal;
in vec4 wLight;
in vec4 wVertex;

out vec4 fragment; // to screenbuffer

void main()
{
    //ambient calculation
    vec4 surfaceColor = texture(colorMap, texCoord); // loading in the colormap
    vec3 ambientColor = vec3(1.0f, 1.0f, 1.0f); // a white light for the ambient
    float intensity = 0.2f; // intensity of the ambient light
    vec3 ambient = intensity *  ambientColor; // calculating the ambient

    // diffuse calculation
    float diffuse =  dot( wNormal, normalize( wLight - wVertex ) ); // diffuse light to vertex

    //specular calculation
    vec3 lightDir = normalize(vec3(wVertex) - vec3(wLight)); // calculating the direction of the light from the light source to the vertex, Normalized
    vec3 cameraDirection = normalize(vec3(cameraPosition) - vec3(wVertex)); // calculating the direction of the camera, from the vertex to the camera, Normalized
	vec3 reflectionDir = reflect(lightDir, vec3(wNormal)); // calculating the reflection direction
	float specular = dot(normalize(cameraDirection), reflectionDir); // calculating the specular by using the dot, dot calculates how much the reflected light is in the same direction as the camera direction
	float gloss = 5.0f; // how intense the light should be
	specular = clamp(pow(specular, gloss), 0.0f, 1.0f); // clamping the specular between 0 and 1 and applying the gloss
    //diffuse = 0; // for testing purposes
	//specular = 0; // for testing purposes

	//calculation fragment
	//fragment = (vec4(diffuse) + vec4(specular) * vec4(1, 0, 0, 1)) * texture( colorMap, texCoord ); // specular and diffuse but no ambient
	fragment = (vec4(ambient, 1) + vec4(diffuse) + (vec4(specular) * vec4(1.0f, 0.0f, 0.0f, 0.0f))) * surfaceColor ; // calculating the final fragment by adding up the ambient, diffuse and specular, multiplying with a red color and the colormap for every coordinate
	//fragment = vec4(ambient,1) ;//* (vec4(diffuse) + vec4(specular) * vec4(1, 0, 0, 1)) ;
}
