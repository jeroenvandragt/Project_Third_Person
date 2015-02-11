#ifndef COLLIDER_H
#define COLLIDER_H


namespace uGE {

    class SphereCollider;
    class GameObject;
	class Collider
	{
		public:
			Collider(GameObject * aParent);
			virtual ~Collider();
			virtual bool collides(Collider * otherCollider) = 0;
			virtual bool collides(Collider * otherCollider, float luaRadius) = 0;
            virtual bool collides(SphereCollider * otherCollider) = 0;
            virtual bool collides(SphereCollider * otherCollider, float luaRadius) = 0;
		protected:
		    GameObject * parent;
		private:
	};
}
#endif // COLLIDER_H
