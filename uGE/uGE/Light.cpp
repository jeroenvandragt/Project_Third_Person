#include "Light.hpp"

namespace uGE {

	Light::Light( std::string name, glm::vec3 position )
	:	GameObject( name )
	{
		setPosition( position );
	}

	Light::~Light()
	{
		//dtor
	}

	void Light::render( Shader * shader )
	{
		//std::cout << "Light" << std::endl;
		//glm::vec3 position = glm::vec3( _transform[3] );
		//glm::vec3 position = glm::vec3( 0,2,5 );
		shader->setUniform( shader->light, glm::vec3( _transform[3] ) );// provide translate column of matrix
	}
}
