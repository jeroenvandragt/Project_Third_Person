#include "Vao.hpp"

#include "Shader.hpp"

namespace uGE {

	Vao::Vao()
	: _id ( 0 )
	{
		//ctor
	}

	Vao::~Vao()
	{
		//dtor
	}

	GLuint Vao::getId()
	{
		return _id;
	}


//	GLuint Vao::createVBO( float * data, unsigned int size, GLuint location, GLuint elements )
//	{
//		GLuint buffer;
//		glGenBuffers( 1, &buffer );
//			glBindBuffer( GL_ARRAY_BUFFER, buffer ); // working on vertices buffer
//				glBufferData( GL_ARRAY_BUFFER, size * elements * sizeof( float ), data, GL_STATIC_DRAW );
//		return buffer;
//	}

	GLuint Vao::createVAO( std::vector< unsigned int > indices, std::vector< glm::vec3 > vertices, std::vector< glm::vec3 > normals, std::vector< glm::vec2 > uvs )
	{
		GLuint vao;
		glGenVertexArrays( 1, &vao );
			glBindVertexArray( vao );
				GLuint buffers[4];
				glGenBuffers( 4, buffers );
					glBindBuffer( GL_ARRAY_BUFFER, buffers[0] ); // working on vertices buffer
						glBufferData( GL_ARRAY_BUFFER, indices.size() * 3 * sizeof( unsigned int ), indices.data(), GL_STATIC_DRAW );

					glBindBuffer( GL_ARRAY_BUFFER, buffers[1] ); // working on vertices buffer
						glBufferData( GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof( float ), vertices.data(), GL_STATIC_DRAW );
							glEnableVertexAttribArray( Shader::vertex );
								glVertexAttribPointer( Shader::vertex, 3, GL_FLOAT, GL_FALSE, 0, 0 );

					glBindBuffer( GL_ARRAY_BUFFER, buffers[2] ); // working on vertices buffer
						glBufferData( GL_ARRAY_BUFFER, normals.size() * 3 * sizeof( float ), normals.data(), GL_STATIC_DRAW );
							glEnableVertexAttribArray( Shader::normal );
								glVertexAttribPointer( Shader::normal, 3, GL_FLOAT, GL_FALSE, 0, 0 );

					glBindBuffer( GL_ARRAY_BUFFER, buffers[3] ); // working on vertices buffer
						glBufferData( GL_ARRAY_BUFFER, uvs.size() * 2 * sizeof( float ), uvs.data(), GL_STATIC_DRAW );
							glEnableVertexAttribArray( Shader::uv );
								glVertexAttribPointer( Shader::uv, 2, GL_FLOAT, GL_FALSE, 0, 0 );

			glBindVertexArray( 0 );
		return vao;
	}
}
