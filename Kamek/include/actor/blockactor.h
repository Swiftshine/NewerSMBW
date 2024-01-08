#ifndef BLOCK_ACTOR_H
#define BLOCK_ACTOR_H
#include <actor/entityactor.h>

class daEnBlockMain_c : public dEn_c {
public:
	u32 _534, _528, _52C, _530;
	Physics physics;
	float _618, _61C, _620;
	u32 _624, _628, _62C;
	float initialY;
	float _634, _638, _63C, _640;
	u32 countdown, _648, _64C;
	u32 _650, _654, _658, _65C;
	u16 _660;
	u8 _662, _663, _664, _665, _666, _667;
	u8 _668, _669, _66A, _66B, _66C, _66D, _66E, _66F;
	u8 _670, _671, _672, _673;
	u8 _674;
	u8 _675, _676, _677, _678, _679, _67A, _67B, _67C;
	u8 _67D, _67E, _67F, _680;
	u32 _684;
	u8 _688, isGroundPound, anotherFlag, _68B, _68C, _68D, _68E, _68F;
	u32 _690;
	u8 _694;

	// Regular methods
	void blockInit(float initialY);
	void blockUpdate();
	u8 blockResult();

	virtual void calledWhenUpMoveBegins();
	virtual void calledWhenDownMoveBegins();

	virtual void calledWhenUpMoveExecutes();
	virtual void calledWhenUpMoveDiffExecutes();
	virtual void calledWhenDownMoveExecutes();
	virtual void calledWhenDownMoveEndExecutes();
	virtual void calledWhenDownMoveDiffExecutes();
	virtual void calledWhenDownMoveDiffEndExecutes();

	virtual void updateScale(bool movingDown);

	// State functions
	virtual void upMove_Begin();
	virtual void upMove_Execute();
	virtual void upMove_End();
	virtual void downMove_Begin();
	virtual void downMove_Execute();
	virtual void downMove_End();
	virtual void downMoveEnd_Begin();
	virtual void downMoveEnd_Execute();
	virtual void downMoveEnd_End();
	virtual void upMove_Diff_Begin();
	virtual void upMove_Diff_Execute();
	virtual void upMove_Diff_End();
	virtual void downMove_Diff_Begin();
	virtual void downMove_Diff_Execute();
	virtual void downMove_Diff_End();
	virtual void downMove_DiffEnd_Begin();
	virtual void downMove_DiffEnd_Execute();
	virtual void downMove_DiffEnd_End();

	static void *PhysicsCallback1;
	static void *PhysicsCallback2;
	static void *PhysicsCallback3;
	static void *OPhysicsCallback1;
	static void *OPhysicsCallback2;
	static void *OPhysicsCallback3;

	USING_STATES(daEnBlockMain_c);
	REF_NINTENDO_STATE(UpMove);
	REF_NINTENDO_STATE(DownMove);
	REF_NINTENDO_STATE(DownMoveEnd);
	REF_NINTENDO_STATE(UpMove_Diff);
	REF_NINTENDO_STATE(DownMove_Diff);
	REF_NINTENDO_STATE(DownMove_DiffEnd);

	~daEnBlockMain_c();
};

typedef daEnBlockMain_c BlockActor;

#endif