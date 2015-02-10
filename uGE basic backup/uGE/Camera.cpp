#include "Camera.hpp"

namespace uGE {

	Camera::Camera( std::string name, glm::vec3 position )
	:	GameObject( name )
	{
		_projection = glm::perspective( 45.0f, 4.f/3.f, 0.1f, 100.0f );
		_transform = glm::inverse( glm::lookAt( position, glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) ) );
		glCullFace( GL_BACK );
	}

	Camera::~Camera()
	{
		//dtor
	}

	void Camera::render( Shader * shader )
	{
		shader->setUniform( shader->projection, _projection );
		shader->setUniform( shader->view, glm::inverse( _transform ) );
	}
}
