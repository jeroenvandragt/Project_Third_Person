#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include "utils/glm.hpp"

#include "Shader.hpp"


namespace uGE {

	class Body;
	class Collider;
	class Controller;
	class GameObject
	{
		public:
			glm::mat4 & transform;

		protected:
			std::string _name;
			glm::mat4 _transform;

			std::vector< GameObject * > children;

			Body 	 * _body;
			Collider * _collider; // for future use by students
			Controller * _controller;
			bool hasCol;

		public:
			GameObject( std::string name );
			virtual ~GameObject();

			std::string getName();

			void addChild( GameObject * child );
			void setBody( Body * body );

            bool hasCollider();
            bool hasBody();
			void setCollider( Collider * collider );
			void setController( Controller * controller );

			void render( Shader * shader, glm::mat4 & parentTransform );
			void update();

            virtual bool hasCollisionWith( GameObject * otherGameObject );
            virtual bool hasCollisionWithLua( GameObject * otherGameObject, float luaRadius );
            void onCollision ( GameObject * otherGameObject );

			void setPosition( glm::vec3 position );
			glm::vec3 getPosition();
			Body * getBody();
            bool hasbody;

	};
}
#endif // GAMEOBJECT_H
