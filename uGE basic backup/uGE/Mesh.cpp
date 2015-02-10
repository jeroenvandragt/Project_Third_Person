#include "Mesh.hpp"

#include <fstream>
#include <map>


namespace uGE {

	Mesh::Mesh()
	{
	}

	Mesh::~Mesh()
	{
	//	glDeleteVertexArrays( 1, & _name );
		glDeleteBuffers( 4, _vbos );
	}

	GLuint Mesh::getIndexBuffer()
	{
		return _vbos[0];
	}
	GLuint Mesh::getVertexBuffer()
	{
		return _vbos[1];
	}
	GLuint Mesh::getNormalBuffer()
	{
		return _vbos[2];
	}
	GLuint Mesh::getUvBuffer()
	{
		return _vbos[3];
	}

	unsigned int Mesh::size()
	{
		return _indices.size();
	}


	Mesh * Mesh::load( std::string filename )
	{
		Mesh * mesh = new Mesh();

		std::ifstream file ( filename.c_str(), std::ios::in );

		if( file.is_open() ){ // file opened succesfully so it exists
			std::vector<glm::vec3> rawVertices; // for the indexed data
			std::vector<glm::vec3> rawNormals; // for the indexed data
			std::vector<glm::vec2> rawUvs; // for the indexed data

			std::map< Face, unsigned int> faces; // used to convert to indexed arrays

			std::string line; // to store each line in
			while( getline( file, line ) ) { // as long as there are lines to be read
				char cmd[10]; // c-type string to store cmd
				cmd[0] = 0;
				sscanf ( line.c_str(), "%10s", cmd ); // get the first string in the line of max 5 chars (c-style)
				if ( strcmp ( cmd, "v" ) == 0 ) { // line with vertex
					glm::vec3 vertex;
					sscanf( line.c_str(), "%10s %f %f %f ", cmd, &vertex.x, &vertex.y, &vertex.z );
					rawVertices.push_back( vertex );
				} else if ( strcmp ( cmd, "vn" ) == 0 ) { // line with normal
					glm::vec3 normal;
					sscanf( line.c_str(), "%10s %f %f %f ", cmd, &normal.x, &normal.y, &normal.z );
					rawNormals.push_back( normal );
				} else if ( strcmp ( cmd, "vt" ) == 0 ) { // line with uv
					glm::vec2 uv;
					sscanf( line.c_str(), "%10s %f %f ", cmd, &uv.x, &uv.y );
					rawUvs.push_back( uv );
				} else if ( strcmp ( cmd, "f" ) == 0 ) { // line with face
					glm::uvec3 vertexIndex; // to store the indices
					glm::uvec3 normalIndex;
					glm::uvec3 uvIndex;
					int count = sscanf( line.c_str(), "%10s %d/%d/%d %d/%d/%d %d/%d/%d", cmd, &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );

					if ( count == 10 ) { // there should be 10 args to be read
						for ( int i = 0; i < 3; ++i ) { // make verticesArray out of indexed array
							Face face = { vertexIndex[i], normalIndex[i], uvIndex[i] };
							std::map< Face, unsigned int>::iterator found = faces.find( face ); // allready oresent ?
							if ( found == faces.end() ) { // face is new
								unsigned int index = faces.size();
								//std::cout << "new i " <<  index << " > " << face.v << "," << face.n << "," << face.t << std::endl;
								faces[ face ] = index;
								mesh->_indices.push_back( index );
								mesh->_vertices.push_back( rawVertices[ vertexIndex[i]-1 ] );
								mesh->_normals.push_back( rawNormals[ normalIndex[i]-1 ] );
								mesh->_uvs.push_back( rawUvs[ uvIndex[i]-1 ] );
							} else { // face already present
								unsigned int index = found->second; // index allready available for the face
								//std::cout << "old i " <<  index << " > " << face.v << "," << face.n << "," << face.t << std::endl;
								mesh->_indices.push_back( index );
							}
						}
					} else { // something is wrong
						std::cout << "Error reading obj, needing v,vn,vt" << std::endl;
						delete mesh; // free the mem from created body
						return 0; // no body read
					}
				}
			}
			file.close();
			mesh->createBuffers();
			std::cout << "Done loading " << filename << " having " << mesh->_vertices.size() << " vertices for " << mesh->_indices.size() << " indices" << std::endl;
			return mesh;
		} else { // file could not be opened;
			std::cout << "Error > Could not load " << filename << std::endl;
			delete mesh;
		}
		return 0;
	}

//	GLuint Mesh::createVAO()
//	{
//		glGenVertexArrays( 1, &_name );
//			glBindVertexArray( _name );
//				glGenBuffers( 4, _vbos );
//					glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _vbos[0] ); // working on indices buffer
//						glBufferData( GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof( unsigned int ), _indices.data(), GL_STATIC_DRAW );
//
//					glBindBuffer( GL_ARRAY_BUFFER, _vbos[1] ); // working on vertices buffer
//						glBufferData( GL_ARRAY_BUFFER, _vertices.size() * 3 * sizeof( float ), _vertices.data(), GL_STATIC_DRAW );
//							glEnableVertexAttribArray( shader->vertex );
//								glVertexAttribPointer( shader->vertex, 3, GL_FLOAT, GL_FALSE, 0, 0 );
//
//					glBindBuffer( GL_ARRAY_BUFFER, _vbos[2] ); // working on normals buffer
//						glBufferData( GL_ARRAY_BUFFER, _normals.size() * 3 * sizeof( float ), _normals.data(), GL_STATIC_DRAW );
//							glEnableVertexAttribArray( shader->normal );
//								glVertexAttribPointer( shader->normal, 3, GL_FLOAT, GL_FALSE, 0, 0 );
//
//					glBindBuffer( GL_ARRAY_BUFFER, _vbos[3] ); // working on uvs buffer
//						glBufferData( GL_ARRAY_BUFFER, _uvs.size() * 2 * sizeof( float ), _uvs.data(), GL_STATIC_DRAW );
//							glEnableVertexAttribArray( shader->uv );
//								glVertexAttribPointer( shader->uv, 2, GL_FLOAT, GL_FALSE, 0, 0 );
//
//			glBindVertexArray( 0 );
//		return _name;
//	}

	GLuint Mesh::createBuffers()
	{
		glGenBuffers( 4, _vbos );

			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _vbos[0] ); // working on indices buffer
				glBufferData( GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof( unsigned int ), _indices.data(), GL_STATIC_DRAW );

			glBindBuffer( GL_ARRAY_BUFFER, _vbos[1] ); // working on vertices buffer
				glBufferData( GL_ARRAY_BUFFER, _vertices.size() * 3 * sizeof( float ), _vertices.data(), GL_STATIC_DRAW );

			glBindBuffer( GL_ARRAY_BUFFER, _vbos[2] ); // working on normals buffer
				glBufferData( GL_ARRAY_BUFFER, _normals.size() * 3 * sizeof( float ), _normals.data(), GL_STATIC_DRAW );

			glBindBuffer( GL_ARRAY_BUFFER, _vbos[3] ); // working on uvs buffer
				glBufferData( GL_ARRAY_BUFFER, _uvs.size() * 2 * sizeof( float ), _uvs.data(), GL_STATIC_DRAW );

		return _name;
	}



}
