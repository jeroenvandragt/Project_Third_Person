#ifndef LIGHT_H
#define LIGHT_H

#include "GameObject.hpp"

namespace uGE {

	class Shader;
	class Light : public GameObject
	{
		public:
			Light( std::string name, glm::vec3 position = glm::vec3( 0,5,0 ) );
			virtual ~Light();

			void render( Shader * shader );
	};
}
#endif // LIGHT_H
