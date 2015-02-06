#version 430

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;

uniform vec3 light; // point light in world

uniform float time;

out float diffuse; // for diffuse light
out vec2 texCoord; // forward uv
out float vTime;

void main()
{
    vec3 vertex3 = vertex;

    vertex3.x += 0.5*sin( time * 2);
    vertex3.y += 0.5*cos( time * 2);


	vec4 wLight  = vec4( light, 1.0f );
	vec4 wVertex = model * vec4( vertex3, 1.0f ); // transform vertex to world
	vec4 wNormal = model * vec4( normal, 0.0f ); // rotate normal to world, note the 0.0 for w. Only works with symmetric scaling

	diffuse =  dot( wNormal, normalize( wLight - wVertex ) ); // diffuse light to vertex

	gl_Position = projection * view * wVertex;

	vTime = time;

    texCoord = uv; // forward to fs
}
