#ifndef SOLID_ON_TOP_COLLIDER_H
#define SOLID_ON_TOP_COLLIDER_H
#include <common.h>
#include <collision/basiccollider.h>
#include <actor/stageactor.h>
class StandOnTopCollider : public BasicCollider {
	public:
		StandOnTopCollider();

		void update();

		void init(dStageActor_c *owner,
				float xOffset, float yOffset, float topYOffset,
				float rightSize, float leftSize,
				s16 rotation, u8 unk_45, Vec2 *scale = 0);

		// void init(dStageActor_c *owner,
		// 		Vec2 *fields4C_50, float topYOffset,
		// 		float rightSize, float leftSize,
		// 		s16 rotation, u8 unk_45, Vec2 *scale = 0);

		void setLeftAndRight(float left, float right);
		void setLeftAndRightScaled(float left, float right, float scaleFactor);

		// 4C and 50 might be X/Y offset. Not affected by rotation
		float _4C, _50, topYOffset, rightSize, leftSize;
};

typedef StandOnTopCollider SolidOnTopCollider;

#endif