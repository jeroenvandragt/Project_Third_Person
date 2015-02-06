#version 430

uniform sampler2D splatMap;
uniform sampler2D colorMap1;
uniform sampler2D colorMap2;
uniform sampler2D colorMap3;
uniform sampler2D colorMap4;

in vec2 texCoord;
in float vTime;

out vec4 fragment; // to screenbuffer

void main()
{
    vec4 tex = texture(splatMap, texCoord);
    vec4    newTex = tex.r * texture( colorMap1 , texCoord );
            newTex += tex.g * texture( colorMap2 , texCoord + vec2(0.02f*sin(vTime),0.03f*cos(vTime)));
            newTex += tex.b * texture( colorMap3 , texCoord );
            newTex += tex.a * texture( colorMap4 , texCoord );


    fragment = newTex;

}
