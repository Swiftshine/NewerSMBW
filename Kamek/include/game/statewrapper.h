#ifndef STATEWRAPPER_H
#define STATEWRAPPER_H
#include <common.h>
#include <statelib.h>
class dActorState_c;
class dActorMultiState_c;


template <class TOwner>
class dStateWrapperBase_c {
public:
	dStateWrapperBase_c(TOwner *pOwner) :
		manager(&pointless, &executor, &dStateBase_c::mNoState), executor(pOwner) { }

	dStateWrapperBase_c(TOwner *pOwner, dState_c<TOwner> *pInitState) :
		manager(&pointless, &executor, pInitState), executor(pOwner) { }

	virtual ~dStateWrapperBase_c() { }

	dStatePointless_c pointless;
	dStateExecutor_c<TOwner> executor;

	dStateMgr_c manager;

	// All these are passed straight through to the manager
	virtual void ensureStateHasBegun() { manager.ensureStateHasBegun(); }
	virtual void execute() { manager.execute(); }
	virtual void endCurrentState() { manager.endCurrentState(); }
	virtual void setState(dStateBase_c *pNewState) { manager.setState(pNewState); }
	virtual void executeNextStateThisTick() { manager.executeNextStateThisTick(); }
	virtual dStateMethodExecutorBase_c *getCurrentStateMethodExecutor() { return manager.getCurrentStateMethodExecutor(); }
	virtual dStateBase_c *getNextState() { return manager.getNextState(); }
	virtual dStateBase_c *getCurrentState() { return manager.getCurrentState(); }
	virtual dStateBase_c *getPreviousState() { return manager.getPreviousState(); }
};

template <class TOwner>
class dStateWrapper_c : public dStateWrapperBase_c<TOwner> {
public:
	dStateWrapper_c(TOwner *pOwner) :
		dStateWrapperBase_c<TOwner>(pOwner) { }

	dStateWrapper_c(TOwner *pOwner, dState_c<TOwner> *pInitState) :
		dStateWrapperBase_c<TOwner>(pOwner, pInitState) { }

	~dStateWrapper_c() { }
};

class MultiStateMgrBase {
public:
	virtual ~MultiStateMgrBase();

	dStateWrapper_c<dActorMultiState_c> s1, s2;
	dStateWrapper_c<dActorMultiState_c> *ptrToStateMgr;

	virtual void ensureStateHasBegun(); // calls vfC on ptrToStateMgr
	virtual void execute(); // calls vf10 on ptrToStateMgr
	virtual void endCurrentState(); // if (isSecondStateMgr()) { disableSecond(); } else { ptrToStateMgr->_vf14(); }
	virtual void setState(dStateBase_c *state); // calls vf18 on ptrToStateMgr
	virtual void executeNextStateThisTick(); // calls vf1C on ptrToStateMgr
	virtual dStateMethodExecutorBase_c *getCurrentStateMethodExecutor(); // calls vf20 on ptrToStateMgr
	virtual dStateBase_c *getNextState(); // calls vf24 on ptrToStateMgr
	virtual dStateBase_c *getCurrentState(); // calls vf28 on ptrToStateMgr
	virtual dStateBase_c *getPreviousState(); // calls vf2C on ptrToStateMgr
	virtual void enableSecondWithState(dStateBase_c *state); // sets ptrToStateMgr to s2, calls vf18 on it
	virtual void disableSecond(); // if (isSecondStateMgr()) { ptrToStateMgr->vf14(); ptrToStateMgr = &s1; }
	virtual bool isSecondStateMgr();
	virtual dStateBase_c *getCurrentStateFromFirst(); // calls vf28 on s1
};

class MultiStateMgr : public MultiStateMgrBase {
public:
	// what the fuck does this do
	~MultiStateMgr();
};

#define REF_NINTENDO_STATE(NAME) \
	static State StateID_##NAME;

#define DECLARE_STATE(NAME) \
	static State StateID_##NAME; \
	void beginState_##NAME(); \
	void executeState_##NAME(); \
	void endState_##NAME();

#define DECLARE_STATE_VIRTUAL(NAME) \
	static State StateID_##NAME; \
	virtual void beginState_##NAME(); \
	virtual void executeState_##NAME(); \
	virtual void endState_##NAME();

#define CREATE_STATE(CLASS, NAME) \
	CLASS::State CLASS::StateID_##NAME \
		(#CLASS "::StateID_" #NAME, \
		&CLASS::beginState_##NAME, \
		&CLASS::executeState_##NAME, \
		&CLASS::endState_##NAME);

#define CREATE_STATE_E(CLASS, NAME) \
	CREATE_STATE(CLASS, NAME) \
	void CLASS::beginState_##NAME() { } \
	void CLASS::endState_##NAME() { }

#define USING_STATES(CLASS) \
	typedef dState_c<CLASS> State;

#endif