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
			Texture 	* _colorMap1;
			Texture 	* _colorMap2;
			Texture 	* _colorMap3;
			Texture 	* _colorMap4;
			Texture 	* _heightMap;
			Texture 	* _splatMap;
			Shader      * _shader;

		public:
			Body( GameObject * parent );
			virtual ~Body();
			void render( Shader * shader, glm::mat4 & transform );
			void setShader(Shader * shader);
			Shader * getShader();
			void setMesh( Mesh * mesh );
			void setTexture1( Texture * colorMap1 );
			void setTexture2( Texture * colorMap2 );
			void setTexture3( Texture * colorMap3 );
			void setTexture4( Texture * colorMap4 );
			void setSplatMap( Texture * splatMap );
			void setHeightMap( Texture * heightMap) ;
	};
}
#endif // BODY_H
