#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "GL/glew.h"

namespace uGE {

	class Texture
	{
		private:
			GLuint _name;


		public:
			Texture( GLuint name );
			virtual ~Texture();

			GLuint getName();

			static Texture * load( std::string filename );
	};
}
#endif // TEXTURE_H
