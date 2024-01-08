#ifndef RIDEABLE_ACTOR_COLLIDER_H
#define RIDEABLE_ACTOR_COLLIDER_H
#include <collision/basiccollider.h>

class RideableActorCollider : public BasicCollider {
	public:
		RideableActorCollider();

		void update();

		void init(dStageActor_c *owner, Vec2 *one, Vec2 *two); // 800DB590
		void init(dStageActor_c *owner, float x1, float y1, float x2, float y2); // 800DB620

		void setPosition(Vec2 *one, Vec2 *two); // 800DB680
		void setPosition(float x1, float y1, float x2, float y2); // 800DB6E0

		Vec2 left, right;
};
#endif