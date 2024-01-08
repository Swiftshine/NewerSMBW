#ifndef BASIC_COLLIDER_H
#define BASIC_COLLIDER_H
#include <common.h>
#include <actor/stageactor.h>

class BasicCollider {
	public:
		BasicCollider();

		virtual ~BasicCollider();
		virtual void update();
		virtual void _vf10();
		virtual void _vf14();

		void clear();
		void addToList();
		void removeFromList();


		dStageActor_c *owner;
		BasicCollider *next, *prev;
		/* dRSomething */ void *ptrToRSomething;

		float rightX, rightY, leftX, leftY;
		float xDiff, yDiff;
		float lastLeftX, lastLeftY;
		float lineLength;
		float leftXDeltaSinceLastCalculation;

		u32 flags;
		s16 rotation;
		u8 type;
		u8 _43;
		u8 isInList;
		u8 _45, _46, _47, _48, _49, _4A;

		static BasicCollider *globalListHead;
};

#endif