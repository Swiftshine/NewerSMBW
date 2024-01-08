#ifndef HITBOX_COLLIDER_H
#define HITBOX_COLLIDER_H
#include <common.h>

class ActivePhysics {
public:
	struct Info; // forward declaration
	typedef void (*Callback)(ActivePhysics *self, ActivePhysics *other);

	struct Info {
		float xDistToCenter;
		float yDistToCenter;
		float xDistToEdge;
		float yDistToEdge;
		u8 category1;
		u8 category2;
		u32 bitfield1;
		u32 bitfield2;
		u16 unkShort1C;
		Callback callback;
	};

	ActivePhysics();
	virtual ~ActivePhysics();

	dStageActor_c *owner;
	u32 _8;
	u32 _C;
	ActivePhysics *listPrev, *listNext;
	u32 _18;
	Info info;
	float trpValue0, trpValue1, trpValue2, trpValue3;
	float firstFloatArray[8];
	float secondFloatArray[8];
	Vec2 positionOfLastCollision;
	u16 result1;
	u16 result2;
	u16 result3;
	u8 collisionCheckType;
	u8 chainlinkMode;
	u8 layer;
	u8 someFlagByte;
	u8 isLinkedIntoList;

	void clear();
	void addToList();
	void removeFromList();

	void initWithStruct(dActor_c *owner, const Info *info);
	void initWithStruct(dActor_c *owner, const Info *info, u8 clMode);

	u16 checkResult1(u16 param);
	u16 checkResult3(u16 param);

	float top();
	float bottom();
	float yCenter();
	float right();
	float left();
	float xCenter();

	// Plus more stuff that isn't needed in the public API, I'm pretty sure.
	
	static ActivePhysics *globalListHead;
	static ActivePhysics *globalListTail;
};
typedef ActivePhysics HitboxCollider;
#endif