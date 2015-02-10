#ifndef VAO_H
#define VAO_H

#include <vector>
#include <GL/glew.h>

#include "Utils/glm.hpp"

namespace uGE {
	class Vao
	{
		public:
			enum Locations {
				vertex = 0, normal = 1, uv = 2,
				colorMap = 10, vertexMap = 11, normalMap = 12,
				seconds = 20,
				light = 30
			};

		protected:
			GLuint _id;

		public:
			Vao();
			virtual ~Vao();

			GLuint getId();

		protected:
			GLuint createVAO( std::vector< unsigned int > indices, std::vector< glm::vec3 > vertices, std::vector< glm::vec3 > normals, std::vector< glm::vec2 > uvs );



	};
}
#endif // VAO_H
