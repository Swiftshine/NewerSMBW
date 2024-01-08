#ifndef PLAYER_H
#define PLAYER_H
#include <common.h>
#include <actor/stageactor.h>
#include <actor/multistateactor.h>

#include <game/statewrapper.h>
class daPlBase_c : public dStageActor_c {
	public:
		// Can't be assed to build full headers right now
		u8 data[0x45C - 0x394];
		float demoMoveSpeed;
		u8 data3[0xEA4 - 0x460];
		dPlayerInput_c input;
		// We're at 0x1008 now
		u8 data2[0x1418 - 0x1008];
		dStateWrapper_c<daPlBase_c> demoStates;
		u32 demoStateParam;
		u32 _1458, _145C;
		u8 _1460;
		dStateWrapper_c<daPlBase_c> states2;

		void justFaceSpecificDirection(int direction);
		void moveInDirection(float *targetX, float *speed);
		bool isReadyForDemoControlAction();

		void setAnimePlayWithAnimID(int id);
		void setAnimePlayStandardType(int id);

		void setFlag(int flag);
		void clearFlag(int flag);
		bool testFlag(int flag);

		static daPlBase_c *findByID(int id);
};

class dAcPy_c : public daPlBase_c {
	public:
		// Can't be assed to build full headers right now
		void *getYoshi(); // 80139A90

		static dAcPy_c *findByID(int id);
};

daPlBase_c *GetPlayerOrYoshi(int id);


class dAc_Py_c : public dStageActor_c {
public:
	u8 data[0x1164 - 0x394];
	ActivePhysics bPhysics;
	ActivePhysics cPhysics;
	ActivePhysics dPhysics;
	ActivePhysics ePhysics;
	
	dAc_Py_c();
	
	int beforeCreate();
	int afterCreate(int);
	int beforeDelete();
	int afterDelete(int);
	int beforeExecute();
	int afterExecute(int);
	int beforeDraw();
	int afterDraw(int);
	
	~dAc_Py_c();
};

class dPlayer : public dActorMultiState_c {

public:
	USING_STATES(dPlayer);
	REF_NINTENDO_STATE(None);
	REF_NINTENDO_STATE(Walk);
	REF_NINTENDO_STATE(Jump);
	REF_NINTENDO_STATE(DemoNone);
	REF_NINTENDO_STATE(DemoWait);
	REF_NINTENDO_STATE(DemoGoal);
	REF_NINTENDO_STATE(DemoControl);
};

typedef dAcPy_c Player;

#endif