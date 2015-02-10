#include <iostream>
#include "Collider.hpp"
#include "GameObject.hpp"

namespace uGE {

	Collider::Collider( GameObject * aParent )
	:   parent( aParent )
	{
		//ctor
	}

	Collider::~Collider()
	{
		//dtor
	}
}
