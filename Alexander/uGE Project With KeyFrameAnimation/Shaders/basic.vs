#version 430

in vec3 vertex;
in vec3 normal;						// attribute-input per normal from normals
in vec2 uv;

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;

uniform vec3 light;     // point light in world

uniform	float time;		// set for all vertices

out vec3 fragVert;
out vec3 fragNormal;
out vec2 fragTexCoord; // forward uv



void main() {
    //vec3 manipulatedVertex = vertex;
	//manipulatedVertex.x += manipulatedVertex.y * manipulatedVertex.y * sin( time ) * 0.25;
	//vec4 wLight  = vec4( light, 1.0f );
	vec4 wVertex = model * vec4( vertex, 1.0f ); // transform vertex to world
	//vec4 wNormal = model * vec4( normal, 0.0f ); // rotate normal to world, note the 0.0 for w. Only works with symmetric scaling

	//diffuse =  dot( wNormal, normalize( wLight - wVertex ) ); // diffuse light to vertex

    gl_Position = projection * view * wVertex;

	fragTexCoord   = uv;    // forward to fs
	fragNormal = normal;    // forward to fs
	fragVert   = vertex;    // forward to fs
}
