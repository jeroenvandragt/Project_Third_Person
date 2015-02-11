#include "GameObject.hpp"
#include "Controller.hpp"
#include "Body.hpp"
#include "Collider.hpp"


namespace uGE {

	GameObject::GameObject( std::string name )
	: transform( _transform ), _name( name ), _body( 0 ), _collider( 0 ), _controller( 0 )
	{
	    hasCol = false;
	    hasbody = false;
	}

	GameObject::~GameObject()
	{
		delete _body;
		delete _collider;
		delete _controller;
	}

	void GameObject::addChild( GameObject * child )
	{
		children.push_back( child );
	}

	std::string GameObject::getName()
	{
		return _name;
	}


	void GameObject::render( Shader * shader, glm::mat4 & parentTransform )
	{
		//std::cout << "Rendering " << _name << std::endl;
		glm::mat4 transform = parentTransform * _transform;
		if ( _body ) _body->render( shader, transform );

		for ( auto i = children.begin(); i != children.end(); ++i ) {
			GameObject * child = (GameObject *) *i;
			child->render( shader, transform );
		}
	}

	void GameObject::setBody( Body * body )
	{

		_body = body;
		hasbody = true;
	}

	bool GameObject::hasBody()
	{
	    return hasbody;
	}

	Body * GameObject::getBody()
	{
	    return _body;
	}

	void GameObject::setCollider( Collider * collider )
	{
	    assert( collider != NULL );
		_collider = collider;
		hasCol = true;
	}

	bool GameObject::hasCollider()
	{
	    return hasCol;
	}

	void GameObject::setController( Controller * controller )
	{
		_controller = controller;
	}

	void GameObject::setPosition( glm::vec3 position )
	{
		_transform[3] = glm::vec4( position, 1.0f );
	}

	glm::vec3 GameObject::getPosition()
	{
        return glm::vec3(transform[3][0],transform[3][1],transform[3][2]);
	}

	void GameObject::update()
	{
		if ( _controller ) _controller->update();

		for ( auto i = children.begin(); i != children.end(); ++i ) {
			GameObject * child = (GameObject *) *i;
			child->update();
		}
	}

    bool GameObject::hasCollisionWith( GameObject * otherGameObject )
    {
        if ( _collider ) {
            _collider->collides( otherGameObject->_collider );
        }
    }

     // bugFix for collisionCall from .lua file.
    // normal collision was called first so collisionCall from lua would never got trough.
    // with this function the collision radius gets increased by "luaRadius" so it hits the object before the normal collision.
    bool GameObject::hasCollisionWithLua( GameObject * otherGameObject, float luaRadius )
    {
        if ( _collider )
        {
            _collider->collides( otherGameObject->_collider, luaRadius );
        }
        //return false;
    }

    void GameObject::onCollision ( GameObject * otherGameObject )
    {
        if ( _controller )
        {
            _controller->onCollision( otherGameObject );
        }
    }
}
