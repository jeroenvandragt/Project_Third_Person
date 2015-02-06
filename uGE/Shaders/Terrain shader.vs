#version 430

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;

uniform float time;
uniform sampler2D heightMap;

uniform vec3 light; // point light in world

out vec2 texCoord; // forward uv
out float vTime;


void main()
{
    vec3 vertex3 = vertex;
    vertex3.y = texture(heightMap, uv).r * 6.0f;// * abs(sin(time));

	vec4 wVertex = model * vec4( vertex3, 1.0f ); // transform vertex to world
	vec4 wNormal = model * vec4( normal, 0.0f ); // rotate normal to world, note the 0.0 for w. Only works with symmetric scaling

	gl_Position = projection * view * wVertex;

    vTime = time; // forward the time to fs
	texCoord = uv; // forward to fs
}
