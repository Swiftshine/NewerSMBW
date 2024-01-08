#ifndef STAGE_ACTOR_H
#define STAGE_ACTOR_H

#include <common.h>
#include <actor/actor.h>
#include <collision/hitboxcollider.h>
#include <collision/collidermgr.h>


class dStageActor_c : public dActor_c {
public:
	enum StageActorType {
		NormalType, PlayerType, YoshiType, EntityType
	};

	u8 _125;
	u32 _128, _12C, directionForCarry, _134, _138, _13C;
	float _140;
	u32 _144;
	ActivePhysics aPhysics;
	collisionMgr_c collMgr;
	u8 classAt2DC[0x34];
	float _310, _314;
	float spriteSomeRectX, spriteSomeRectY;
	float _320, _324, _328, _32C, _330, _334, _338, _33C, _340, _344;
	u8 direction;
	u8 currentZoneID;
	u8 _34A, _34B;
	u8 *spriteByteStorage;
	u16 *spriteShortStorage;
	u16 spriteFlagNum;
	u64 spriteFlagMask;
	u32 _360;
	u16 spriteSomeFlag;
	u8 _366, _367;
	u32 _368;
	u8 eatenState;	// 0=normal,2=eaten,4=spit out
	u8 _36D;
	Vec scaleBeforeBeingEaten;
	u32 _37C, lookAtMode, _384, _388;
	u8 stageActorType;
	u8 which_player;		// _38D
	u8 disableFlagMask, currentLayerID;
	u8 deleteForever;
	u8 appearsOnBackFence, _392, _padding;

	dStageActor_c();

	int beforeCreate();
	int afterCreate(int);
	int beforeDelete();
	int afterDelete(int);
	int beforeExecute();
	int afterExecute(int);
	int beforeDraw();
	int afterDraw(int);

	const char *GetExplanationString();

	virtual bool isOutOfView(); // does stuff with BG_GM
	virtual void kill(); // nullsub here, defined in StageActor. probably no params
	virtual int _vf68(); // params unknown. return (1) might be bool
	virtual u8 *_vf6C(); // returns byte 0x38D
	virtual Vec2 _vf70(); // returns Vec Actor.pos + Vec Actor.field_D0
	virtual int _vf74(); // params unknown. return (1) might be bool
	virtual void itemPickedUp(); // params unknown. nullsub
	virtual void _vf7C(); // params unknown. nullsub
	virtual void eatIn(); // copies Actor.scale into StageActor.somethingRelatedToScale
	virtual void disableEatIn(); // params unknown. nullsub
	virtual void _vf88(); // params unknown. nullsub
	virtual bool _vf8C(void *other); // dAcPy_c/daPlBase_c? return (1) is probably bool. seems related to EatOut. uses vfA4
	virtual bool _vf90(dStageActor_c *other); // does something with scores
	virtual void _vf94(void *other); // dAcPy_c/daPlBase_c? modifies This's position
	virtual void removeMyActivePhysics();
	virtual void addMyActivePhysics();
	virtual void returnRegularScale(); // the reverse of vf80, yay
	virtual void _vfA4(void *other); // AcPy/PlBase? similar to vf94 but not quite the same
	virtual float _vfA8(void *other); // AcPy/PlBase? what DOES this do...? does a bit of float math
	virtual void _vfAC(void *other); // copies somethingRelatedToScale into scale, then multiplies scale by vfA8's return
	virtual void killedByLevelClear(); // plays Wm_en_burst_s at actor position
	virtual void _vfB4(); // params unknown. nullsub
	virtual void _vfB8(); // params unknown. nullsub
	virtual void _vfBC(); // params unknown. nullsub
	virtual void _vfC0(); // params unknown. nullsub
	virtual void _vfC4(); // params unknown. nullsub
	virtual void _vfC8(Vec2 *p, float f); // does stuff including effects and playing PLAYER_SE_OBJ/GROUP_BOOT/SE_OBJ_CMN_SPLASH
	virtual void _vfCC(Vec2 *p, float f); // mostly same as vfC8, but uses PLAYER_SE_OBJ/GROUP_BOOT/SE_OBJ_CMN_SPLASH_LAVA
	virtual void _vfD0(Vec2 *p, float f); // mostly same as vfC8, but uses PLAYER_SE_OBJ/GROUP_BOOT/SE_OBJ_CMN_SPLASH_POISON

	// I'll add methods as I need them
	bool outOfZone(Vec3 pos, float* rect, u8 zone);
	bool checkZoneBoundaries(u32 flags); // I think this method is for that, anyway
	void Delete(u8 param1);				// fBase_c::Delete(void);

	~dStageActor_c();


	static dStageActor_c *create(Actors type, u32 settings, Vec *pos, S16Vec *rot, u8 layer);
	static dStageActor_c *createChild(Actors type, dStageActor_c *parent, u32 settings, Vec *pos, S16Vec *rot, u8 layer);

	// these are valid while in onCreate
	static u8 *creatingByteStorage; // 0x80429FF4
	static u16 creatingFlagID; // 0x80429FF8
	static u64 creatingFlagMask; // 0x8042A000
	static u8 creatingLayerID; // 0x8042A000
};


#endif