#ifndef SPHERECOLLISION_H
#define SPHERECOLLISION_H
#include "../utils/glm.hpp"

#include "../Collider.hpp"

namespace uGE
{
    class SphereCollider : public Collider
    {
        private:

        public:
            SphereCollider( GameObject * aParent, float aRadius = 1.0f );
            virtual ~SphereCollider();

            float radius;

            virtual bool collides( Collider * otherCollider );
            virtual bool collides( SphereCollider * otherCollider );
    };
}

#endif // SPHERECOLLISION_H
