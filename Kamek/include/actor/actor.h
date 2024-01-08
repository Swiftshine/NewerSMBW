#ifndef ACTOR_H
#define ACTOR_H
#include <game/base/base.h>

class dActor_c : public dBase_c {
public:
	LinkListEntry link_actor;
	mMtx matrix;
	Vec pos;
	Vec last_pos;
	Vec pos_delta;
	Vec pos_delta2;
	Vec scale;
	Vec speed;
	Vec max_speed;
	S16Vec rot;
	S16Vec _106;
	u32 _10C;
	u32 _110;
	float y_speed_inc;
	u32 _118;
	float x_speed_inc;
	u32 _120;
	bool visible;

	dActor_c();

	virtual void specialDraw1();
	virtual void specialDraw2();
	virtual int _vf58();
	virtual void _vf5C();

	~dActor_c();

	void UpdateObjectPosBasedOnSpeedValuesReal();
	void HandleXSpeed();
	void HandleYSpeed();
};

#endif