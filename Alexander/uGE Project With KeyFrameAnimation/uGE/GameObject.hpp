#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include "utils/glm.hpp"

#include "Shader.hpp"
#include "Mesh.hpp"


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


            //----- Animation

			std::vector<Mesh*> frames;
			std::vector<float> frameDuration;
			std::vector<std::string> frameNames;
			std::vector<std::string> cycleNames;

			float frameTime;
			unsigned int currentFrame;
			bool paused;


		public:
			GameObject( std::string name );
			virtual ~GameObject();

			std::string getName();

			void addChild( GameObject * child );
			void setBody( Body * body );

            bool hasCollider();
			void setCollider( Collider * collider );
			void setController( Controller * controller );

			Body * getBody();

			void render( Shader * shader, glm::mat4 & parentTransform );
			void update( float step );

            virtual bool hasCollisionWith( GameObject * otherGameObject );
            void onCollision ( GameObject * otherGameObject );

			void setPosition( glm::vec3 position );
			glm::vec3 getPosition();

			//------- Animation

            void addFrame(Mesh * aMesh, float duration, std::string frameName, std::string cycleName);

            void playCycle( float step );
            void setNextFrame();
            void setStartFrame();
            void setCycle( std::string );
            void setFrame( std::string );

            void setPaused(bool);
            bool getPaused();

	};
}
#endif // GAMEOBJECT_H
