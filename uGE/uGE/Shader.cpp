#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Mesh.hpp"
#include "Texture.hpp"

namespace uGE {

	Shader::Shader( GLuint program )
	:	_program( program )
	{
		vertex 			= glGetAttribLocation( _program, "vertex" );
		normal 			= glGetAttribLocation( _program, "normal" );
		uv 					= glGetAttribLocation( _program, "uv" );
		projection	= glGetUniformLocation( _program, "projection" );
		view				= glGetUniformLocation( _program, "view" );
		model				= glGetUniformLocation( _program, "model" );
		colorMap1		= glGetUniformLocation( _program, "colorMap1" );
		colorMap2		= glGetUniformLocation( _program, "colorMap2" );
		colorMap3		= glGetUniformLocation( _program, "colorMap3" );
		colorMap4		= glGetUniformLocation( _program, "colorMap4" );
		splatMap		= glGetUniformLocation( _program, "splatMap" );
		heightMap		= glGetUniformLocation( _program, "heightMap" );
		lightCount	= glGetUniformLocation( _program, "lightCount" );
		light				= glGetUniformLocation( _program, "light" );
		time				= glGetUniformLocation( _program, "time" );
		slot				= glGetUniformLocation( _program, "slot" );
	}

	Shader::~Shader()
	{
		//dtor
	}

	void Shader::use()
	{
		glUseProgram( _program );

	}

	void Shader::render( GLuint size )
	{
		//std::cout << "Shader render " << mesh->getName() << std::endl;
//		GLuint name = mesh->getName();
		//glBindVertexArray( name );
		//std::cout << "Shader render between" << mesh->size() << std::endl;

		glDrawElements( GL_TRIANGLES, size, GL_UNSIGNED_INT, 0 );
		//std::cout << "Shader render after" << mesh->getName() << std::endl;
	}

	void Shader::setUniform( GLuint location, float value )
	{
		glUniform1f( location, value );
	}

	void Shader::setUniform( GLuint location, glm::mat4 matrix )
	{
		glUniformMatrix4fv( location, 1, GL_FALSE, glm::value_ptr( matrix ) );
	}

	void Shader::setUniform( GLuint location, glm::vec3 vector )
	{
		glUniform3fv( location, 1, glm::value_ptr( vector ) );
	}

	void Shader::setTexture( GLuint location, GLuint slot, Texture * texture )
	{
		glActiveTexture( GL_TEXTURE0 + slot ); // units numbered as uniform locations with slot number
			glBindTexture( GL_TEXTURE_2D, texture->getName() );
				glUniform1i( location, slot );
	}

	void Shader::setAttrib( GLuint indices )
	{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indices ); // working on indices buffer
	}

	void Shader::setAttrib( GLuint location, GLuint elements, GLuint buffer )
	{
		glBindBuffer( GL_ARRAY_BUFFER, buffer );
		glEnableVertexAttribArray( location );
		glVertexAttribPointer( location, elements, GL_FLOAT, GL_FALSE, 0, 0 );
	}


	Shader * Shader::load( std::string vs, std::string fs )
	{
		GLuint program = linkProgram( vs, fs );

		if ( program !=  0 ) { // success
			Shader * shader = new Shader( program );
			//shader->_program = program;
			return shader;
		}
		return 0;
	}


	GLuint Shader::compileShader( GLenum type, std::string name )
	{
		std::cout << "Reading shader " << name << std::endl;
		std::ifstream file( name.c_str() );

		// note, next has changed due to a problem while debugging, it gave a C000 error when extrating the string through a sstream.
		std::string shaderCode, line;
		while( getline( file, line ) ) shaderCode += line+"\n";
		std::cout << "Compiling shader " << std::endl;
		//std::cout << shaderCode << std::endl;

		// Compile Vertex Shader
		const char * shaderCodePointer = shaderCode.c_str();
		GLuint shaderId = glCreateShader( type  ); // get shader id
		glShaderSource( shaderId, 1, &shaderCodePointer, NULL );
		glCompileShader( shaderId );

		// Check compiler result
		GLint result = GL_FALSE;
		glGetShaderiv( shaderId, GL_COMPILE_STATUS, &result);

		if ( result ) {
			std::cout << "Shader compiled ok" << std::endl;
			return shaderId;
		} else { // get error message
			int count;
			glGetShaderiv( shaderId, GL_INFO_LOG_LENGTH, &count);
			//std::vector<char> errorMessage( count+1 );
			char errorMessage[ count+1 ];
			glGetShaderInfoLog( shaderId, count, NULL, errorMessage);
			std::cout << errorMessage << std::endl;
			return 0; // no shader id
		}
	}

	// link the two shaders and return the program id
	GLuint Shader::linkProgram ( std::string vertexShaderFileName, std::string fragmentShaderFileName )
	{
		// Link the program
		GLuint program = glCreateProgram();
		glAttachShader( program, compileShader( GL_VERTEX_SHADER, vertexShaderFileName ) );
		glAttachShader( program, compileShader( GL_FRAGMENT_SHADER, fragmentShaderFileName ) );
		glLinkProgram( program );

		// Check the program
		GLint result = GL_FALSE;
		glGetProgramiv( program, GL_LINK_STATUS, &result );
		if ( result ) {
			std::cout << "program linked ok" << std::endl;
			return program;
		} else { // error, show message
			int count;
			glGetProgramiv( program, GL_INFO_LOG_LENGTH, &count );
			//std::vector<char> ProgramErrorMessage( max(count, int(1)) );
			char errorMessage[ count+1 ];
			glGetProgramInfoLog( program, count, NULL, errorMessage );
			std::cout << errorMessage << std::endl;
			return 0;
		}
	}


}
