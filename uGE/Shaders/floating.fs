#version 430

uniform sampler2D colorMap;

in vec2 texCoord;

in float diffuse;
in float vTime;

out vec4 fragment; // to screenbuffer

void main()
{

	fragment = diffuse * texture( colorMap, texCoord + vec2(0.02f*sin(vTime),0.03f*cos(vTime)) );

}
