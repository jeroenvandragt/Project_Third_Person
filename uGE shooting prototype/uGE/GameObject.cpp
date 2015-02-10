#include <cassert>

#include "GameObject.hpp"
#include "Controller.hpp"
#include "Body.hpp"
#include "Collider.hpp"


namespace uGE {

	GameObject::GameObject( std::string name )
	: transform( _transform ), _name( name ), _body( 0 ), _collider( 0 ), _controller( 0 )
	{
	    hasCol = false;
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

	glm::vec3 GameObject::getDirection()
    {
    return glm::vec3(transform[2]);
    }

	Body * GameObject::getBody()
	{
	    return _body;
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

    void GameObject::onCollision ( GameObject * otherGameObject )
    {
        if ( _controller )
        {
            _controller->onCollision( otherGameObject );
        }
    }

    void GameObject::setParent(GameObject * aParent)
    {
        assert (aParent != NULL);
        parent = aParent;
    }

    void GameObject::add( GameObject * child )
    {
        assert( child != NULL );
        children.push_back( child );
        child->setParent(this);
    }

void GameObject::removeChild(GameObject * child)
    {
        assert(child != NULL);
        for (unsigned int i = 0; i < children.size(); ++i) {
            if (children[i] == child) children.erase(children.begin() + i);
        }
    }
}
