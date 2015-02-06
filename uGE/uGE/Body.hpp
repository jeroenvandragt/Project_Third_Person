#ifndef BODY_H
#define BODY_H

#include "GameObject.hpp"
#include "Utils/glm.hpp"
#include "Shader.hpp"

namespace uGE {

	class Mesh;
	class Body
	{
		private:
			GameObject 	* _parent;
			Mesh 		* _mesh;
			Shader      * _shader;
			Texture 	* _colorMap1;
			Texture 	* _colorMap2;
			Texture 	* _colorMap3;
			Texture 	* _colorMap4;
			Texture 	* _splatMap;
			Texture 	* _heightMap;

		public:
			Body( GameObject * parent );
			virtual ~Body();
			void render( Shader * shader, glm::mat4 & transform );
			void setMesh( Mesh * mesh );
            void setShader( Shader * shader );
            Shader * getShader();
			void setTexture1( Texture * texture );
			void setTexture2( Texture * texture );
			void setTexture3( Texture * texture );
			void setTexture4( Texture * texture );
			void setSplatMap( Texture * texture );
			void setHeightMap( Texture * texture );
	};
}
#endif // BODY_H
