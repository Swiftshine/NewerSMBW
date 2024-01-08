#ifndef COLLIDER_MGR_H
#define COLLIDER_MGR_H
#include <common.h>
#include <collision/solidcollider.h>
#include <collision/sensor.h>
class dStageActor_c;

class collisionMgr_c {
	public:
		collisionMgr_c();
		virtual ~collisionMgr_c();

		dStageActor_c *owner;
		sensorBase_s *pBelowInfo, *pAboveInfo, *pAdjacentInfo;

		VEC3 *pPos, *pLastPos, *pSpeed;
		VEC3 specialSpeedOffset;
		float xDeltaMaybe, yDeltaMaybe;
		float _34, _38;
		u32 _3C, _40, _44, _48;
		float initialXAsSetByJumpDai;
		/*dClass2DC_c*/void *pClass2DC;
		u32 _54;
		Physics *sCollBelow;
		Physics *sCollAbove;
		Physics *sCollAdjacentLast, *sCollAdjacent[2];
		collisionMgr_c *_6C, *_70, *_74;
		collisionMgr_c *_78[2];
		Physics *_80[2];
		u32 outputMaybe;
		u32 _8C;
		u32 someStoredBehaviourFlags, someStoredProps;
		char whichPlayerOfParent____;
		char whichController____;
		u16 _9A, _9C;
		u32 tileBelowProps;
		u8 tileBelowSubType, lastTileBelowSubType;
		u32 tileAboveProps;
		u8 tileAboveSubType, lastTileAboveSubType;
		u32 adjacentTileProps[2];
		u8 adjacentTileSubType[2];
		u8 _BA, _BB;
		u8 _BC; // &8 makes able to enter mini pipes?
		u8 currentSlopeType;
		s16 currentSlopeAngle;
		u8 currentFlippedSlopeType;
		s16 currentFlippedSlopeAngle;
		u32 _C4;
		u16 currentAdjacentSlopeAngle;
		u32 currentFenceType; // 0=null 1=ladder 2=fence
		Physics *_D0;
		float _D4;
		float _D8;
		float _DC;
		u8 touchedSpikeFlag;
		s8 maxTouchedSpikeType;
		u8 currentSlopeDirection, _E3, onGround_maybe, chainlinkMode;
		u8 *pLayerID;
		u8 layer;
		bool enteredPipeIsMini;

		// Setup
		void clear1();
		void clear2();
		void init(dStageActor_c *owner, const sensorBase_s *belowInfo, const sensorBase_s *aboveInfo, const sensorBase_s *adjacentInfo);

		u32 calculateBelowCollision();
		u32 calculateAboveCollision(u32 value);
		u32 calculateAdjacentCollision(float *pFloat=0);

		bool setBelowSubType(u32 magic); // maybe not public?

		u8 getBelowSubType();
		u8 getAboveSubType();
		u8 getAdjacentSubType(int direction);

		int returnSomethingBasedOnSlopeAngle();
		bool doesSlopeGoUp();

		int getSlopeYDirectionForXDirection(int direction);
		int getSlopeYDirectionForXDirection(int direction, int slopeType);
		s16 getAngleOfSlopeInDirection(int direction);
		s16 getAngleOfSlopeWithXSpeed(float xSpeed);
		s16 getAngleOfSlopeInDirection2(int thing);
		s16 getAngleOfFlippedSlopeInDirection(int thing);
		s16 getAngleOfFlippedSlopeInDirection2(int thing);

		static bool checkPositionForTileOrSColl(float x, float y, u8 layer, u32 unk, u32 mask);
		static int getPartialBlockExistenceAtPos(float x, float y, u8 layer);
		static bool isPartialBlockOrBlockSolidAtPos(float x, float y, u8 layer);
		static u32 getTileBehaviour1At(float x, float y, u8 layer);
		static u32 getTileBehaviour2At(float x, float y, u8 layer);
		static u32 getTileBehaviour1At(u16 x, u16 y, u8 layer);
		static u32 getTileBehaviour2At(u16 x, u16 y, u8 layer);

		u8 getOwnerStageActorType() const;
		u32 returnOutputAnd18000() const;
		bool isOnTopOfTile() const;

		u32 s_80071210(dStageActor_c *player);
		bool tryToEnterPipeBelow(VEC3 *pOutVec, int *pOutEntranceID);
		bool tryToEnterPipeAbove(VEC3 *pOutVec, int *pOutEntranceID);
		bool tryToEnterAdjacentPipe(VEC3 *pOutVec, int unk, int *pOutEntranceID, float fp1, float fp2);
		u32 detectFence(lineSensor_s *info);
		bool detectClimbingPole(lineSensor_s *info);

		bool s_80072440(VEC2 *v2one, VEC2 *v2two, float *pOutFloat);
		bool s_800728C0(VEC2 *vecParam, float *pOutFloat);

		u32 calculateBelowCollisionWithSmokeEffect();

		u32 calculateAdjacentCollisionAlternate(float *pFloat=0);

		static void setupEverything(int wrapType);

		bool getBelowSensorHLine(hLine_s *outLine);
		bool getAboveSensorHLine(hLine_s *outLine);
		bool getAdjacentSensorVLine(vLine_s *outLine, int direction);

		void s_800731E0(Physics *sColl, VEC3 *somePos);

		void clearStoredSColls();
		void s_80075090();
		bool s_800751C0(Physics *sColl, collisionMgr_c *what);
		collisionMgr_c *s_80075230(Physics *sColl);

		static int checkPositionForLiquids(float x, float y, int layer, float *unkDestFloat = 0);
		static int s_80075560(float x, float y, int layer, float *destFloat);
		static bool s_80075750(VEC2 *pVec);
		static bool s_80075780(s16 *pAngle);

		static bool sub_800757B0(VEC3 *vec, float *what, u8 layer, int p6, char p7);


		enum SlopeTypes {
			SLOPE_EDGE = 10,
			SLOPE_TYPE_COUNT = 19
		};
		struct slopeParams_s {
			float basePos, colHeight;
		};
		static const slopeParams_s slopeParams[SLOPE_TYPE_COUNT];
		static const slopeParams_s flippedSlopeParams[SLOPE_TYPE_COUNT];
		static const u8 slopeKinds[SLOPE_TYPE_COUNT];
		static const u8 slopeDirections[SLOPE_TYPE_COUNT];
};

typedef collisionMgr_c ColliderMgr;
#endif