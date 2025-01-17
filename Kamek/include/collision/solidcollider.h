#ifndef SOLID_COLLIDER_H
#define SOLID_COLLIDER_H
#include <common.h>

class Physics {
public:
	struct Unknown {
		Unknown();
		~Unknown();

		float x, y;
	};

	struct Info {
		float x1, y1, x2, y2; // Might be distance to center/edge like APhysics
		void *otherCallback1, *otherCallback2, *otherCallback3;
	};

	Physics();
	~Physics();

	dActor_c *owner;
	Physics *next, *prev;
	u32 _C, _10, _14, _18, _1C, _20, _24, _28, _2C, _30, _34;
	void *somePlayer;
	u32 _3C;
	void *otherCallback1, *otherCallback2, *otherCallback3;
	void *callback1, *callback2, *callback3;
	float lastX, lastY;
	Unknown unkArray[4];
	float x, y;
	float _88, _8C;
	float diameter;
	Vec lastActorPosition;
	float _A0, _A4, last_A0, last_A4, _B0, _B4;
	u32 _B8;
	s16 *ptrToRotationShort;
	s16 currentRotation;
	s16 rotDiff;
	s16 rotDiffAlt;
	u32 isRound;
	u32 _CC;
	// Flag 4 is icy
	u32 flagsMaybe;
	u32 _D4, _D8;
	u8 isAddedToList, _DD, layer;
	u32 id;

	void addToList();
	void removeFromList();

	void baseSetup(dActor_c *actor, void *otherCB1, void *otherCB2, void *otherCB3, u8 t_DD, u8 layer);

	// note: Scale can be a null pointer (in that case, it'll use 1.0)
	void setup(dActor_c *actor,
			float x1, float y1, float x2, float y2,
			void *otherCB1, void *otherCB2, void *otherCB3,
			u8 t_DD, u8 layer, Vec2 *scale = 0);

	void setup(dActor_c *actor,
			Vec2 *p1, Vec2 *p2,
			void *otherCB1, void *otherCB2, void *otherCB3,
			u8 t_DD, u8 layer, Vec2 *scale = 0);

	void setup(dActor_c *actor, Info *pInfo, u8 t_DD, u8 layer, Vec2 *scale = 0);

	// radius might be diameter? dunno
	void setupRound(dActor_c *actor,
			float x, float y, float radius,
			void *otherCB1, void *otherCB2, void *otherCB3,
			u8 t_DD, u8 layer, Vec2 *scale = 0);

	void setRect(float x1, float y1, float x2, float y2, Vec2 *scale = 0);
	void setRect(Vec2 *p1, Vec2 *p2, Vec2 *scale = 0);

	void setX(float value);
	void setY(float value);
	void setWidth(float value);
	void setHeight(float value);
	
	void setPtrToRotation(s16 *ptr);

	void update();
	
	static Physics* globalListHead;
	static Physics* globalListTail;
	// todo: more stuff that might not be relevant atm
};

typedef Physics SolidCollider;

#endif