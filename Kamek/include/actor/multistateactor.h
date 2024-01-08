#ifndef MULTI_STATE_ACTOR_H
#define MULTI_STATE_ACTOR_H

#include <game/statewrapper.h>
#include <actor/stageactor.h>

class dActorState_c : public dStageActor_c {
public:
	dActorState_c();
	~dActorState_c();

	dStateWrapper_c<dActorState_c> acState;

	virtual void beginState_Gegneric();
	virtual void executeState_Gegneric();
	virtual void endState_Gegneric();
};


class dActorMultiState_c : public dStageActor_c {
public:
	~dActorMultiState_c();

	MultiStateMgr acState;

	virtual void doStateChange(dStateBase_c *state); // might return bool? overridden by dEn_c
	virtual void _vfD8(); // nullsub ??
	virtual void _vfDC(); // nullsub ??
	virtual void _vfE0(); // nullsub ??
};


#endif