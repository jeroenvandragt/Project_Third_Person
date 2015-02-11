#include <iostream>
#include "SphereCollider.hpp"
#include "../GameObject.hpp"
#include "../utils/glm.hpp"


namespace uGE
{
    SphereCollider::SphereCollider( GameObject * aParent, float aRadius )
    :	Collider( aParent ), radius( aRadius )
    {
    }

    SphereCollider::~SphereCollider()
    {
    }

    bool SphereCollider::collides( Collider * otherCollider )
    {
        //std::cout << "sphere collider with collider" << std::endl;
        return otherCollider->collides( this );
    }

      bool SphereCollider::collides( Collider * otherCollider, float luaRadius )
    {
        //std::cout << "sphere collider with collider" << std::endl;
        return otherCollider->collides( this, luaRadius );
    }


    bool SphereCollider::collides( SphereCollider * otherCollider )
    {
        glm::vec3 parentPosition = glm::vec3(parent->transform[3]);
        glm::vec3 otherParentPosition = glm::vec3(otherCollider->parent->transform[3]);
        float comRadius = radius + otherCollider->radius;
        //std::cout << objDist.z << " " << comRadius << std::endl;

        float dx = glm::abs(parentPosition[0] - otherParentPosition[0]);
        float dy = glm::abs(parentPosition[1] - otherParentPosition[1]);
        float dz = glm::abs(parentPosition[2] - otherParentPosition[2]);

        if (comRadius * comRadius > (dx * dx + dy * dy + dz * dz))
        {
            return true;
        }
        return false;
    }
    // bugFix for collisionCall from .lua file.
    // normal collision was called first so collisionCall from lua would never got trough.
    // with this function the collision radius gets increased by "luaRadius" so it hits the object before the normal collision.
    bool SphereCollider::collides( SphereCollider * otherCollider, float luaRadius )
    {
        glm::vec3 parentPosition = glm::vec3(parent->transform[3]);
        glm::vec3 otherParentPosition = glm::vec3(otherCollider->parent->transform[3]);
        float comRadius = radius + otherCollider->radius + luaRadius;
        //std::cout << objDist.z << " " << comRadius << std::endl;

        float dx = glm::abs(parentPosition[0] - otherParentPosition[0]);
        float dy = glm::abs(parentPosition[1] - otherParentPosition[1]);
        float dz = glm::abs(parentPosition[2] - otherParentPosition[2]);

        if (comRadius * comRadius > (dx * dx + dy * dy + dz * dz))
        {
            return true;
        }
        return false;
    }
}
