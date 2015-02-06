#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.hpp"

namespace uGE {

	class Camera : public GameObject
	{
		private:
			glm::mat4 _projection;
			glm::mat4 _view;
		public:
			Camera( std::string name, glm::vec3 position = glm::vec3( 0, 2, 4 ) );
			virtual ~Camera();

			void render( Shader * shader );
	};
}
#endif // CAMERA_H
