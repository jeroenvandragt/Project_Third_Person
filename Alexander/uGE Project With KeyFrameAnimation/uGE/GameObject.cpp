#include "GameObject.hpp"
#include "Controller.hpp"
#include "Body.hpp"
#include "Collider.hpp"


namespace uGE {

	GameObject::GameObject( std::string name )
	: transform( _transform ), _name( name ), _body( 0 ), _collider( 0 ), _controller( 0 ), frameTime( 0.0f ), currentFrame( 0 ), paused( false )
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

	Body * GameObject::getBody()
	{
	    return _body;
	}



	void GameObject::update( float step)
	{
		if ( _controller ) _controller->update();

        //std::cout << _body->getMesh() << std::endl;

		for ( auto i = children.begin(); i != children.end(); ++i ) {
			GameObject * child = (GameObject *) *i;
			child->update( step );
		}

        if(frames.size() > 1) playCycle( step );
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


    //---------------------Animation



    void GameObject::addFrame(Mesh * aMesh, float duration, std::string frameName, std::string cycleName)
    {
        // Add Meshes, PlayTime and Names to Lists

        frames.push_back(aMesh);
        frameDuration.push_back(duration);
        frameNames.push_back(frameName);
        cycleNames.push_back(cycleName);

        frameTime = frameDuration[0];
    }

    void GameObject::playCycle( float step )
    {
        // Play Animatie with step = deltaTime

        if( !paused ) frameTime -= step;
        if( frameTime < 0 ) setNextFrame();     //If frametime is over, goto next frame
    }

    void GameObject::setNextFrame()
    {
        if (currentFrame != cycleNames.size() - 1) {
            if (cycleNames[currentFrame] == cycleNames[currentFrame + 1])
            {
                std::cout << " going next frame " << std::endl;
                currentFrame++;
            }
            else setStartFrame();
        }
        else setStartFrame();

        frameTime = frameDuration[currentFrame];
        _body->setMesh(frames[currentFrame]);
    }

    void GameObject::setStartFrame()
    {
        //std::cout << " set start frame called " << std::endl;

        std::string firstFrame = cycleNames[currentFrame] + "Start";
        for (unsigned int i = 0; i < frameNames.size(); ++i) {
            if (frameNames[i] == firstFrame) {
                currentFrame = i;
                break;
            }
        }
    }

    void GameObject::setCycle( std::string cycleTag )
    {
        if (cycleNames[currentFrame] != cycleTag) {
            for (unsigned int i = 0; i < cycleNames.size(); ++i) {
                if (cycleNames[i] == cycleTag) {
                    if (cycleNames[currentFrame] != cycleTag) currentFrame = i;
                    break;
                }
            }
            frameTime = frameDuration[currentFrame];
            setNextFrame();
        }
    }

    void GameObject::setFrame( std::string frameTag )
    {
        if (cycleNames[currentFrame] != frameTag) {
            for (unsigned int i = 0; i < cycleNames.size(); ++i) {
                if (cycleNames[i] == frameTag) {
                    if (cycleNames[currentFrame] != frameTag) currentFrame = i;
                    break;
                }
            }
            frameTime = frameDuration[currentFrame];
            setNextFrame();
        }
    }

    void GameObject::setPaused( bool state )
    {
        paused = state;
    }

    bool GameObject::getPaused()
    {
        return paused;
    }

}
