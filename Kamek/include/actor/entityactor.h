#ifndef ENTITY_ACTOR_H
#define ENTITY_ACTOR_H

// i couldn't figure out a better name for dEn_c, sorry

#include <actor/multistateactor.h>

class dEn_c : public dActorMultiState_c {
public:
	EntityDeathInfo deathInfo;
	u32 _434;
	u16 _438;
	u32 _43C;
	Vec velocity1, velocity2;
	u8 _458, _459, _45A, _45B, _45C, _45D, _45E;
	u32 _460;
	Vec initialScale;
	float _470;
	u32 _474, _478;
	dEn_c *_47C;
	u32 _480;
	//FIXME verify that size fits
	//u8 classAt484[0x4EC - 0x484];
	freezeMgr_c frzMgr;
	u32 _4EC;
	float _4F0, _4F4, _4F8;
	u32 flags_4FC;
	u16 counter_500, counter_502;
	u16 counter_504[4];
	u16 counter_50C;
	u32 _510, _514, _518;
	void *_51C;
	dEn_c *_520;

	dEn_c();

	int afterCreate(int);
	int beforeExecute();
	int afterExecute(int);
	int beforeDraw();

	void kill();

	void eatIn();
	void disableEatIn();
	bool _vf8C(void *other); // AcPy/PlBase?
	void _vfAC();
	void _vfCC(Vec2 *p, float f);
	void _vfD0(Vec2 *p, float f);

	void doStateChange(dStateBase_c *state); // might return bool, dunno

	// Now here's where the fun starts.
	
	virtual bool preSpriteCollision(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool prePlayerCollision(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool preYoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther);

	virtual bool stageActorCollision(ActivePhysics *apThis, ActivePhysics *apOther);
	
	virtual void spriteCollision(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual void playerCollision(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual void yoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther);

	// WHAT A MESS
	virtual bool collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool collisionCat5_Mario(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool _vf108(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool _vf110(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool collisionCat8_FencePunch(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool _vf120(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool collisionCat11_PipeCannon(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther);
	virtual bool collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther);

	virtual void _vf140(dStageActor_c *actor);
	virtual void powBlockActivated(bool isNotMPGP);
	virtual void _vf148(); // deletes actors held by Class484 and other stuff
	virtual void _vf14C(); // deletes actors held by Class484 and makes an En Coin Jump
	virtual u32 canBePowed(); // reads some bits from a value in Class1EC
	virtual void eatenByYoshiProbably(); // nullsub, params unknown
	virtual void playHpdpSound1(); // plays PLAYER_SE_EMY/GROUP_BOOT/SE_EMY_DOWN_HPDP_S or _H
	virtual void playEnemyDownSound1();
	virtual void playEnemyDownComboSound(void *player); // AcPy_c/daPlBase_c?
	virtual void playHpdpSound2(); // plays PLAYER_SE_EMY/GROUP_BOOT/SE_EMY_DOWN_HPDP_S or _H
	virtual void _vf168(); // nullsub, params unknown

	// State Functions
	virtual void dieFumi_Begin(); // does something involving looping thruogh players
	virtual void dieFumi_Execute(); // does movement and some other stuff
	virtual void dieFumi_End(); // nullsub
	virtual void dieFall_Begin(); // does something involving looping thruogh players
	virtual void dieFall_Execute(); // does movement and some other stuff
	virtual void dieFall_End(); // nullsub
	virtual void dieBigFall_Begin(); // calls vf178 [dieFall_Begin]
	virtual void dieBigFall_Execute(); // does movement and some other stuff (but less than 170 and 17C)
	virtual void dieBigFall_End(); // calls vf180 [dieFall_End]
	virtual void dieSmoke_Begin(); // spawns Wm_en_burst_m effect and then removeMyActivePhysics
	virtual void dieSmoke_Execute(); // deletes actor with r4=1
	virtual void dieSmoke_End(); // nullsub
	virtual void dieYoshiFumi_Begin(); // spawns Wm_mr_yoshistep effect and then removeMyActivePhysics
	virtual void dieYoshiFumi_Execute(); // deletes actor with r4=1
	virtual void dieYoshiFumi_End(); // nullsub
	virtual void dieIceVanish_Begin(); // lots of weird stuff
	virtual void dieIceVanish_Execute(); // deletes actor with r4=1
	virtual void dieIceVanish_End(); // nullsub
	virtual void dieGoal_Begin(); // nullsub
	virtual void dieGoal_Execute(); // nullsub
	virtual void dieGoal_End(); // nullsub
	virtual void dieOther_Begin(); // deletes actor with r4=1
	virtual void dieOther_Execute(); // nullsub
	virtual void dieOther_End(); // nullsub
	virtual void eatIn_Begin(); // nullsub
	virtual void eatIn_Execute(); // changes to EatNow on one condition, otherwise calls vfAC
	virtual void eatIn_End(); // nullsub
	virtual void eatNow_Begin(); // nullsub
	virtual void eatNow_Execute(); // nullsub
	virtual void eatNow_End(); // nullsub
	virtual void eatOut_Begin(); // nullsub
	virtual void eatOut_Execute(); // nullsub
	virtual void eatOut_End(); // nullsub
	virtual void hitSpin_Begin(); // nullsub
	virtual void hitSpin_Execute(); // nullsub
	virtual void hitSpin_End(); // nullsub
	virtual void ice_Begin(); // does stuff with Class484 and lots of vf's
	virtual void ice_Execute(); // tons of stuff with Class484
	virtual void ice_End(); // sets a field in Class484 to 0

	virtual void spawnHitEffectAtPosition(Vec2 pos);
	virtual void doSomethingWithHardHitAndSoftHitEffects(Vec pos);
	virtual void playEnemyDownSound2();
	virtual void add2ToYSpeed();
	virtual bool _vf218(); // stuff with floats and camera
	virtual void _vf21C(); // does stuff with the speeds
	virtual void _vf220(void *player); // hurts player
	virtual void _vf224(); // stores a couple of values into the struct at 464
	virtual void _vf228(); // more fun stuff with 464 and floats
	virtual bool CreateIceActors(); // does stuff involving ICE_ACTORs and arrays
	virtual void _vf230(); // "relatedToPlayerOrYoshiCollision" apparently. nullsub, params unknown for now.
	virtual void _vf234(); // nullsub, params unknown
	virtual void _vf238(); // calls vf34 on class394, params unknown
	virtual void _vf23C(); // nullsub, params unknown
	virtual void _vf240(); // nullsub, params unknown
	virtual int _vf244(); // returns 0. might be bool. params unknown
	virtual int _vf248(int something); // does some math involving field510 and [7,7,4,0] and param
	virtual void bouncePlayerWhenJumpedOn(void *player);
	virtual void addScoreWhenHit(void *other); // Other is dPlayer
	virtual void _vf254(void *other);
	virtual void _vf258(void *other);
	virtual void _vf25C(void *other); // calls vf250
	virtual void _vf260(void *other); // AcPy/PlBase? plays the SE_EMY_FUMU_%d sounds based on some value
	virtual void _vf264(dStageActor_c *other); // if other is player or yoshi, do Wm_en_hit and a few other things
	virtual void _vf268(void *other); // AcPy/PlBase? plays the SE_EMY_DOWN_SPIN_%d sounds based on some value
	virtual void spawnHitEffectAtPositionAgain(Vec2 pos);
	virtual void playMameStepSound(); // SE_EMY_MAME_STEP at actor position
	virtual void _vf274(); // nullsub, params unknown
	virtual void _vf278(void *other); // AcPy/PlBase? plays the SE_EMY_YOSHI_FUMU_%d sounds based on some value
	virtual void _vf27C(); // nullsub, params unknown

	~dEn_c();

	static void collisionCallback(ActivePhysics *one, ActivePhysics *two);

	void doSpriteMovement();
	bool CheckIfPlayerBelow(float,float);

	void stuffRelatingToCollisions(float, float, float);

	void checkLiquidImmersionAndKillIfTouchingLava(Vec *pos, float effectScale);
	void checkLiquidImmersion(Vec2 *effectivePosition, float effectScale);

	void killWithSpecifiedState(dStageActor_c *killedBy, VEC2 *effectiveSpeed, dStateBase_c *state, u32 _unused=0);
	void bouncePlayer(void* player, float bounceHeight);

	void killByDieFall(dStageActor_c *killedBy);

	// States
	USING_STATES(dEn_c);
	REF_NINTENDO_STATE(DieFumi);
	REF_NINTENDO_STATE(DieFall);
	REF_NINTENDO_STATE(DieBigFall);
	REF_NINTENDO_STATE(DieSmoke);
	REF_NINTENDO_STATE(DieIceVanish);
	REF_NINTENDO_STATE(DieYoshiFumi);
	REF_NINTENDO_STATE(DieGoal);
	REF_NINTENDO_STATE(DieOther);
};

typedef dEn_c EntityActor;

#endif