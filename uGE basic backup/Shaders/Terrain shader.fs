#version 430


uniform sampler2D splatMap;
uniform sampler2D colorMap1;
uniform sampler2D colorMap2;
uniform sampler2D colorMap3;
uniform sampler2D colorMap4;
uniform float time;

in vec2 texCoord;
in float diffuse;

in vec3 fragVertex;
//in vec3 fragNormal;

out vec4 fragment; // to screenbuffer

void main()
{

	vec4 newSplatMap = texture( splatMap, texCoord );
	vec4 newTex = newSplatMap.r * texture( colorMap1 , texCoord );
        newTex += newSplatMap.g * texture( colorMap2 , texCoord + vec2(0.2f*time,0.2f));//*sin(time));
        newTex += newSplatMap.b * texture( colorMap3 , texCoord );
        newTex += newSplatMap.a * texture( colorMap4 , texCoord );
	fragment = newTex;

}
