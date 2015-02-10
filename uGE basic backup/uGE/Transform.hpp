#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Utils/glm.hpp"


// sould hold local and global transform. local is maniplated bij behaviors and
class Transform
{
	public:
		Transform();
		virtual ~Transform();

		glm::vec3 position();

		void rotate( float angle, glm::vec3 axis );
};

#endif // TRANSFORM_H
