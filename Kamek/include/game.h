#ifndef __KAMEK_GAME_H
#define __KAMEK_GAME_H

#include <common.h>
#include <sdk/gx.h>
#include <sdk/tpl.h>
#define offsetof(type, member)	((u32) &(((type *) 0)->member))

#include <g3dhax.h>

template <typename T>
inline T min(T one, T two) { return (one < two) ? one : two; }
template <typename T>
inline T max(T one, T two) { return (one > two) ? one : two; }
template <typename T>
inline T clamp(T value, T one, T two) { return (value < one) ? one : ((value > two) ? two : value); }

#define M_PI 3.14159265358979323846
#define M_PI_2 (M_PI / 2)

extern "C" {
int wcslen(const wchar_t *str);
wchar_t *wcscpy(wchar_t *dest, const wchar_t *src);
int strlen(const char *str);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, int num);
int strncmp(const char *str1, const char *str2, int num);

float atan(float x);
float atan2(float y, float x);

float cos(float x);
float sin(float x);
float ceil(float x);
float floor(float x);
}
enum Direction {
	RIGHT = 0,
	LEFT = 1,
	UP = 2,
	DOWN = 3,
};


bool DVD_Start();
bool DVD_End();
bool DVD_StillLoading(void *dvdclass2);
void DVD_LoadFile(void *dvdclass, char *folder, char *file, void *callbackData);
void DVD_FreeFile(void *dvdclass2, char *file);

extern void *DVDClass;

inline void *GetDVDClass() {
	return DVDClass;
}

inline void *GetDVDClass2() {
	return (void*)(((u32)GetDVDClass())+4);
}

void *DVD_GetFile(void *dvdclass2, const char *arc, const char *file);
void *DVD_GetFile(void *dvdclass2, const char *arc, const char *file, u32 *length);

int MakeRandomNumber(int count);
int MakeRandomNumberForTiles(int count);


extern int Player_Active[4];
extern int Player_ID[4];
extern int Player_Powerup[4];
extern int Player_Flags[4];
extern int Player_Lives[4];
extern int Player_Coins[4];

struct StartLevelInfo {
	int maybeUnused;
	unsigned char replayTypeMaybe; // 0x04
	unsigned char entrance; // 0x05
	unsigned char areaMaybe; // 0x06
	unsigned char unk4; // 0x07
	unsigned int purpose; // 0x08
	unsigned char world1; // 0x0C
	unsigned char level1; // 0x0D
	unsigned char world2; // 0x0E
	unsigned char level2; // 0x0F
};
extern bool DontShowPreGame;
extern StartLevelInfo RESTART_CRSIN_LevelStartStruct;

class GMgr8 {
	public:
		virtual ~GMgr8();

		int _4;
		float _8, _C;
		u32 _10, _14;
		u8 _18, _19, _1A, _1B, _1C;
		u32 _20, _24, _28, _2C, _30;
};

struct GMgrA0 {
	u32 _0, _4, _8;
	u8 _C;
};

class GameMgr {
	public:
		virtual ~GameMgr();

		u32 _4;
		GMgr8 eight;
		u32 _3C, _40, _44, _48, _4C, _50, _54, _58;
		u32 _5C, _60, _64, _68, _6C;
		u32 _70[10];
		u8 _98;
		u32 _9C;
		GMgrA0 _A0[40];
		u32 _320[10], _348[10];
		u32 _370, _374, _378, _37C;
		u8 switchPalaceFlag;
		u32 CharIDs[4];
		u8 _394;
		u8 _395[10];
		u8 _39F[10];
		u8 _3A9[10];
		u8 _3B3;
		u32 numberToInsertInThing[7];
		u32 msgCategory, msgID;
		u8 _3D8;
		u8 currentControllerType, layoutShadowFlag;
		u32 numberToInsertInThing10, numberToInsertInThing11;
		u32 _3E4, _3E8, _3EC, _3F0, _3F4, _3F8;
		// unmapped data from 3FC..AEC (0x6F0)
		u8 _3FC[0x6F0];
		u32 _AEC, _AF0, _AF4, _AF8;
		u8 _AFC, _AFD, _AFE[88];
		u8 _B56[4];
		u8 _B5A, _B5B;

		void giveOneStockPowerup(int type); // 800BB330
		void takeOneStockPowerup(int type); // 800BB380
		int getStockPowerupCount(int type); // 800BB3D0
		void resetStockPowerupCount(int type); // 800BB410
};

extern GameMgr *GameMgrP;
inline void *GetGameMgr() {
	return GameMgrP;
}

bool QueryPlayerAvailability(int id);
void DoStartLevel(void *gameMgr, StartLevelInfo *sl);


// Level Conditions
//     1 : Has Toad Block
//     2 : Is Regular Level (has star coins, etc)
//  0x10 : Has Normal Exit
//  0x20 : Has Secret Exit
//  0x40 : Warp Cannon
//  0x80 : 1up/Green Mushroom House
// 0x100 : Red Mushroom House
// 0x200 : Star/Yellow Mushroom House
void SetSomeConditionShit(int world, int level, unsigned int bits);

bool IsWideScreen();

#define GAMEMGR_GET_AFC(gmgr) (*((bool*)(((u32)(gmgr))+0xAFC)))

#include <game/savedata.h>
#include <game/remocon.h>

int SearchForIndexOfPlayerID(int id);

bool CheckIfContinueShouldBeActivated();

bool CheckIfMenuShouldBeCancelledForSpecifiedWiimote(int num);

void StartTitleScreenStage(bool realDemo, int sceneParam);

bool CheckIfWeCantDoStuff();

u32 QueryGlobal5758(u32 check);

void SaveGame(void *classDoesntMatter, bool isQuick);

#include <actor/actorlist.h>
void *CreateParentedObject(short classID, void *parent, int settings, char something);
void *CreateChildObject(short classID, void *parent, int settings, int unk1, int unk2);


#define WIPE_FADE 0
#define WIPE_CIRCLE 1
#define WIPE_BOWSER 2
#define WIPE_WAVY 3
#define WIPE_MARIO 4
#define WIPE_CIRCLE_s 5

void ActivateWipe(int type);

typedef void (*ScreenDrawFunc)();

extern ScreenDrawFunc *CurrentDrawFunc;
void WorldMapDrawFunc();
void GameSetupDrawFunc();

void GameSetup__LoadScene(void *self); // 0x80919560
void FreeScene(int id);

void WpadShit(int unk); // 0x8016F780

void *BgTexMng__LoadAnimTile(void *self, int tileset, short tile, char *name, char *delays, char reverse); // 0x80087B60

extern void *GameHeaps[];


class dFlagMgr_c {
public:
	dFlagMgr_c();

	enum ActionFlag {
		ACTIVATE = 1,
		TICKS = 2
	};

	u64 flags;
	float _8[64], _108[64];
	u8 _208[64];
	u64 _248[64];
	u8 _448[64];

	u32 ticksRemainingForAction[64];
	u8 actionFlag[64];
	u32 _5C8[64]; // somehow sound related?! assigned by last param to set(); only checked for == 0
	u8 _6C8; // assigned -1 by FlagMgr, and other values by the Switch object, nothing else though

	void setup(bool isNewLevel);
	void applyAndClearAllTimedActions(); // only used when setup(true) is called
	void execute();

	void set(u8 number, int delay, bool activate, bool reverseEffect, bool makeNoise, u32 unknown=0);

	u8 findLowestFlagInSet(u32 unk, u64 set);

	void setSpecial(u8 number, float to8, float to108, u8 to208, u32 unk, u64 to248);
	float get8(u8 number);
	float get108(u8 number);
	u8 get208(u8 number);
	u64 get248(u8 number);
	u8 get448(u8 number);

	// convenience inline functions which may or may not actually exist in Nintendo's original code
	u64 mask(u8 number) { return (u64)1 << number; }
	bool active(u8 number) { return (flags & mask(number)) != 0; }
	bool inactive(u8 number) { return (flags & mask(number)) == 0; }

	static dFlagMgr_c *instance;
};


class WLClass {
public:
	u32 _0;
	u32 _4;
	u32 _8;
	u32 _otherDatum[38];

	static WLClass *instance;

	void demoControlAllPlayers();
	void disableDemoControl(bool uselessVar);
};


class dStage32C_c {
public:

	u32 bulletData1[32];
	u32 bulletData2[32];
	u32 enemyCombos[4];
	u32 somethingAboutHatenaBalloons;
	u32 redCoinCount[4];
	u32 _124[4];
	u32 greenCoinsCollected;
	u32 hasKilledEnemyThisTick_maybe;
	u16 booID;
	u32 _bigBooID;
	u16 bulletBillCount;
	u32 bombCount;
	u32 goombaCount;
	u32 enemyKillCounter;
	u32 another_counter;
	u32 freezeMarioBossFlag;
	u32 aboutMortonBigPile;
	u32 somethingAboutPunchingChainlink;
	u32 currentBigHanaMgr;
	u32 _16C;
	u8 penguinCount;
	u32 pokeyTimer;

	static dStage32C_c *instance;
};




// No idea if these actually exist or not
class mRect {
	public:
		float x, y, width, height;
};

class mRect16 {
	public:
		short x, y, width, height;
};


class mMtx {
	Mtx data;

	public:
	mMtx() { }

	mMtx(float _00, float _01, float _02, float _03,
			float _10, float _11, float _12, float _13,
			float _20, float _21, float _22, float _23);

	float* operator[](int row) { return data[row]; }

	operator Mtx *() { return &data; }

	/* Create New Ones */
	void zero();
	void identity() { MTXIdentity(data); }

	void translation(float x, float y, float z) { MTXTrans(data, x, y, z); }
	void scale(float x, float y, float z) { MTXScale(data, x, y, z); }

	void rotationX(s16 *amount);
	void rotationY(s16 *amount);
	void rotationZ(s16 *amount);

	/* Applied Manipulations */
	void applyTranslation(float x, float y, float z) { MTXTransApply(data, data, x, y, z); }
	void applyScale(float x, float y, float z) { MTXScaleApply(data, data, x, y, z); }

	void applyRotationX(s16 *amount);
	void applyRotationY(s16 *amount);
	void applyRotationZ(s16 *amount);

	void applyRotationYXZ(s16 *x, s16 *y, s16 *z);
	void applyRotationZYX(s16 *x, s16 *y, s16 *z);

	/* Get Stuff */
	void getTranslation(Vec *target);

	void getUnknown(S16Vec *target);
};



namespace nw4r {
	namespace math {
		float CosFIdx(float);
		float SinFIdx(float);
		void SinCosFIdx(float *s, float *c, float);
	}

namespace ut {
	// this isn't 100% accurate because it doesn't use templates
	// or detail::LinkListImpl, but oh well
	// I don't need the methods anyway.

	class LinkListNode {
	public:
		LinkListNode *next;
		LinkListNode *prev;
	};

	class LinkList {
	public:
		int count;
		LinkListNode initialNode;
	};

	class Color : public GXColor {
		public:
			GXColor& operator=(const GXColor &other) {
				*((u32*)this) = *((u32*)&other);
				return *this;
			}
	};

	class Rect {
	public:
		f32 left;
		f32 top;
		f32 right;
		f32 bottom;
	};

	template <class T>
	class TagProcessorBase { };
}

namespace lyt {
	class Pane; // forward declaration
	class DrawInfo;

	class AnimTransform; // I'll do these later
	class AnimResource;
	class AnimationLink;
	class ResourceAccessor;
	class Group;
	class GroupContainer;

	namespace detail {
		class TexCoordAry {
			public:
				TexCoordAry();
				void Free();
				void Reserve(u8 count);
				void SetSize(u8 count);
				void Copy(const void *source, u8 count);

				u8 reservedSize, usedSize;
				void *data;
		};
	}

	class Layout {
	public:
		Layout();
		virtual ~Layout();

		virtual bool Build(const void *data, ResourceAccessor *resAcc);

		virtual AnimTransform *CreateAnimTransform();
		virtual AnimTransform *CreateAnimTransform(const void *data, ResourceAccessor *resAcc);
		virtual AnimTransform *CreateAnimTransform(const AnimResource &res, ResourceAccessor *resAcc);

		virtual void BindAnimation(AnimTransform *anim);
		virtual void UnbindAnimation(AnimTransform *anim);
		virtual void UnbindAllAnimation();
		virtual bool BindAnimationAuto(const AnimResource &res, ResourceAccessor *resAcc);

		virtual void SetAnimationEnable(AnimTransform *anim, bool unk);

		virtual void CalculateMtx(const DrawInfo &info);

		virtual void/*?*/ Draw(const DrawInfo &info);
		virtual void/*?*/ Animate(ulong flag);

		virtual void/*?*/ SetTagProcessor(ut::TagProcessorBase<wchar_t> *tagProc);

		ut::LinkList animations;

		Pane *rootPane;
		GroupContainer *groupContainer;

		float width;
		float height;
	};


	class DrawInfo {
	public:
		DrawInfo();
		virtual ~DrawInfo();

		Mtx matrix;
		float left;
		float top;
		float right;
		float bottom;
		float scaleX;
		float scaleY;
		float alpha;
		u8 _50; // this is actually a bitfield. todo: investigate how CW handles bitfields, and so on
	};


	class TexMap {
		public:
			void *image, *palette;
			u16 width, height;
			f32 minLOD, magLOD;
			u16 lodBias, palEntryNum;
			u32 settingsBitfield;

			int getFormat() { return (settingsBitfield >> 28); }
			void setFormat(int fmt) {
				settingsBitfield = (fmt << 28) | (settingsBitfield & 0xFFFFFFF);
			}

			void ReplaceImage(TPLPalette *tpl, unsigned long id);
	};

	class Material {
	public:
		virtual ~Material();

		// cheating a bit here
		u8 _[0x3C];
		// this is actually a pointer to more stuff, not just texmaps
		TexMap *texMaps;
	};

	class Pane {
	public:
		//Pane(nw4r::lyt::res::Pane const *); // todo: this struct
		Pane(void *);
		virtual ~Pane();

		virtual void *GetRuntimeTypeInfo() const;
		virtual void CalculateMtx(const DrawInfo &info);

		virtual void Draw(const DrawInfo &info);
		virtual void DrawSelf(const DrawInfo &info);
		virtual void Animate(ulong flag);
		virtual void AnimateSelf(ulong flag);

		virtual ut::Color GetVtxColor(ulong id) const;
		virtual void SetVtxColor(ulong id, ut::Color color);
		virtual uchar GetColorElement(ulong id) const;
		virtual void SetColorElement(ulong id, uchar value);
		virtual uchar GetVtxColorElement(ulong id) const;
		virtual void SetVtxColorElement(ulong id, uchar value);

		virtual Pane *FindPaneByName(const char *name, bool recursive);
		virtual Material *FindMaterialByName(const char *name, bool recursive);

		virtual void/*?*/ BindAnimation(AnimTransform *anim, bool unk1, bool unk2);
		virtual void UnbindAnimation(AnimTransform *anim, bool unk);
		virtual void UnbindAllAnimation(bool unk);
		virtual void UnbindAnimationSelf(AnimTransform *anim);

		virtual ut::LinkListNode *FindAnimationLinkSelf(AnimTransform *anim);
		virtual ut::LinkListNode *FindAnimationLinkSelf(const AnimResource &anim);

		virtual void SetAnimationEnable(AnimTransform *anim, bool unk1, bool unk2);
		virtual void SetAnimationEnable(const AnimResource &anim, bool unk1, bool unk2);

		virtual ulong GetMaterialNum() const;
		virtual Material *GetMaterial() const;
		virtual Material *GetMaterial(ulong id) const;

		virtual void LoadMtx(const DrawInfo &info);

		void AppendChild(Pane *child);

		ut::Rect GetPaneRect(const DrawInfo &info) const;

		ut::LinkListNode *AddAnimationLink(AnimationLink *link);

		Vec2 GetVtxPos() const;


		ut::LinkListNode parentLink;
		Pane *parent;

		ut::LinkList children;
		ut::LinkList animations;

		Material *material;

		Vec trans;
		Vec rotate;
		Vec2 scale;
		Vec2 size;

		Mtx calcMtx;
		Mtx effectiveMtx;

		float _B4;

		u8 alpha;
		u8 effectiveAlpha;
		u8 origin;
		u8 flag;

		char name[0x11];
		char userdata[9];

		u8 paneIsOwnedBySomeoneElse;
		u8 _D7;

		void SetVisible(bool value) {
			if (value)
				flag |= 1;
			else
				flag &= ~1;
		}
	};

	class TextBox : public Pane {
	public:
		TextBox(void *, void *); // todo: TextBox((res::TextBox const *,ResBlockSet const &))
		~TextBox();

		void *GetRuntimeTypeInfo() const;

		void DrawSelf(const DrawInfo &info);

		ut::Color GetVtxColor(ulong id) const;
		void SetVtxColor(ulong id, ut::Color color);
		uchar GetVtxColorElement(ulong id) const;
		void SetVtxColorElement(ulong id, uchar value);

		void LoadMtx(const DrawInfo &info);

		virtual void AllocStringBuffer(u16 size);
		virtual void FreeStringBuffer();

		virtual u16 SetString(const wchar_t *str, u16 destOffset = 0);
		virtual u16 SetString(const wchar_t *str, u16 destOffset, u16 length);

		wchar_t *stringBuf;

		ut::Color colour1, colour2;
		void *font; // actually a ut::ResFont or whatever

		float fontSizeX, fontSizeY;
		float lineSpace, charSpace;

		void *tagProc; // actually a TagProcessor

		u16 bufferLength;
		u16 stringLength;

		u8 alignment;
		u8 flags;
	};

	class Picture : public Pane {
	public:
		Picture(void *, void *); // todo: Picture((res::Picture const *,ResBlockSet const &))
		~Picture();

		void *GetRuntimeTypeInfo() const;

		void DrawSelf(const DrawInfo &info);

		ut::Color GetVtxColor(ulong id) const;
		void SetVtxColor(ulong id, ut::Color color);
		uchar GetVtxColorElement(ulong id) const;
		void SetVtxColorElement(ulong id, uchar value);

		virtual void Append(const GXTexObj &obj);

		ut::Color colours[4];
		detail::TexCoordAry texCoords;
	};
}



namespace g3d {
struct CameraData {
	Mtx cameraMtx;
	Mtx44 projectionMtx;

	u32 flags;

	VEC3 camPos;
	VEC3 camUp;
	VEC3 camTarget;
	VEC3 camRotate;
	float camValue;

	int projectionType;
	float fovy;
	float aspect;
	float near, far;
	float top, bottom, left, right;

	float _CC, _D0, _D4, _D8;

	float viewportX, viewportY;
	float viewportWidth, viewportHeight;
	float viewportNearZ, viewportFarZ;

	int scissorX, scissorY, scissorWidth, scissorHeight;
	int scissorOffsetX, scissorOffsetY;
};

class Camera {
public:
	struct PostureInfo {
		int mode;
		VEC3 up;
		VEC3 target;
		VEC3 cameraRotate;
		float cameraTwist;
	};
	CameraData *data;
	Camera(CameraData *pCamera);
	void Init();
	void Init(u16 efbWidth, u16 efbHeight, u16 xfbWidth, u16 xfbHeight, u16 viWidth, u16 viHeight);
	void SetPosition(const VEC3 &pos);
	void GetPosition(VEC3 *pos) const;
	void SetPosture(const PostureInfo &info);
	void SetCameraMtxDirectly(const Mtx &mtx);
	void SetPerspective(f32 fovy, f32 aspect, f32 near, f32 far);
	void SetOrtho(f32 top, f32 bottom, f32 left, f32 right, f32 near, f32 far);
	void SetProjectionMtxDirectly(const Mtx44 *pMtx);
	void SetScissor(u32 xOrigin, u32 yOrigin, u32 width, u32 height);
	void SetScissorBoxOffset(s32 xOffset, s32 yOffset);
	void SetViewport(f32 xOrigin, f32 yOrigin, f32 width, f32 height);
	void SetViewportZRange(f32 near, f32 far);
	void SetViewportJitter(u32 field);
	void GetViewport(f32 *xOrigin, f32 *yOrigin, f32 *width, f32 *height, f32 *near, f32 *far) const;
	void GetCameraMtx(Mtx *pMtx) const;
	void GetProjectionMtx(Mtx44 *pMtx) const;
	void GXSetViewport() const;
	void GXSetProjection() const;
	void GXSetScissor() const;
	void GXSetScissorBoxOffset() const;
};

namespace G3DState {
	GXRModeObj *GetRenderModeObj();
}
}
}


VEC2 GetSomeSizeRelatedBULLSHIT();
Vec CalculateSomethingAboutRatio(float, float, float, float);
float CalculateSomethingElseAboutRatio();

nw4r::g3d::CameraData *GetCameraByID(int id);

namespace EGG { class Screen; };
void DoSomethingCameraRelatedWithEGGScreen(int id, EGG::Screen *screen);

int GetCurrentCameraID(); // 80164C80
void SetCurrentCameraID(int id); // 80164C90

void LinkScene(int id); // 80164D50
void UnlinkScene(int id); // 80164CD0

void SceneCalcWorld(int sceneID); // 80164E10
void SceneCameraStuff(int sceneID); // 80164EA0

void CalcMaterial(); // 80164E90
void DrawOpa(); // 80164F70
void DrawXlu(); // 80164F80

bool ChangeAlphaUpdate(bool enable); // 802D3270
bool ChangeColorUpdate(bool enable); // 802D3210

void DoSpecialDrawing1(); // 8006CAE0
void DoSpecialDrawing2(); // 8006CB40

void SetupLYTDrawing(); // 80163360
void ClearLayoutDrawList(); // 801632B0

void RenderAllLayouts(); // 800067A0
void DrawAllLayoutsBeforeX(int x); // 80163440
void DrawAllLayoutsAfterX(int x); // 801634D0
void DrawAllLayoutsAfterXandBeforeY(int x, int y); // 80163560

void RenderEffects(int v1, int v2); // 80093F10

void RemoveAllFromScnRoot(); // 80164FB0
void Reset3DState(); // 80165000

extern "C" void GXDrawDone(); // 801C4FE0

extern "C" u32 VIGetNextField();



namespace m2d {
	class Base_c /*: public nw4r::ut::Link what's this? */ {
	public:
		u32 _00;
		u32 _04;

		Base_c();
		virtual ~Base_c();
		virtual void draw(); // don't call this directly

		void scheduleForDrawing();

		u8 drawOrder;
	};

	class Simple_c : public Base_c {
	public:
		nw4r::lyt::Layout layout;
		nw4r::lyt::DrawInfo drawInfo;

		u32 _84;
		float _88;
		float _8C;
		float _90;
		u32 _94;

		Simple_c();
		~Simple_c();

		void draw();
		virtual void _vf10();
		virtual void _vf14();
	};
}



namespace EGG {
	class Frustum {
	public:
		int projType; // 0 = ortho, 1 = perspective.. who needs GXEnum.h anyway
		int isCentered;
		float width;
		float height;
		float fovy;
		float dunno;
		float near;
		float far;
		float center_x_maybe;
		float center_y_maybe;
		float horizontalMultiplier;
		float verticalMultiplier;
		float unk3;
		short some_flag_bit;


		// isCentered might actually be isNotCentered, dunno
		Frustum(u32 projType, Vec2 size, bool isCentered, float near, float far); // 802C6D20
		Frustum(Frustum &f); // 802C6D90
		virtual ~Frustum(); // 802C75F0

		virtual void loadDirectly(); // 802C7050
		virtual void loadIntoCamera(nw4r::g3d::Camera cam); // 802C7070

		void setOrtho(float top, float bottom, float left, float right, float near, float far); // 802C6DD0

		void setFovy(float newFovy); // 802C6F60

		void getCenterPointsBasedOnPos(float x, float y, float *destX, float *destY); // 802C6FD0

		// no idea what this does
		float getSomethingForPerspective(float blah); // 802C7020


	protected:
		// not all of these might be protected, dunno

		void copyAllFields(Frustum &f); // 802C6EE0

		static void saveSomething(float f1, float f2, float f3, float f4); // 802C70C0
		static void restoreSomething(float *f1, float *f2, float *f3, float *f4); // 802C70E0

		void loadPerspective(); // 802C7110
		void loadOrtho(); // 802C7140

		void setCameraPerspective(nw4r::g3d::Camera cam); // 802C7170
		void setCameraOrtho(nw4r::g3d::Camera cam); // 802C71E0

		void getPerspectiveProjMtx(Mtx44 *mtx); // 802C7250
		void getPerspectiveProjv(float *ptr); // 802C72E0
		void getOrthoProjv(float *ptr); // 802C73A0

		void getOrthoVars(float *top, float *bottom, float *left, float *right); // 802C7480
	};


	class Screen : public Frustum {
		public:
			struct Info {
				float viewportX, viewportY, viewportWidth, viewportHeight;
				float viewportNearZ, viewportFarZ;

				int scissorX, scissorY, scissorWidth, scissorHeight;
				int scissorOffsetX, scissorOffsetY;
			};

			Screen(); // 802D0FB0; creates perspective screen with basic settings
			Screen(Screen *pParent, bool isCentered, float m40, float m44, float width, float height); // 802D1080
			Screen(Screen &s); // 802D1140

			~Screen(); // not called by the retail game.. dunno how to make CodeWarrior do this, who gives a fuck

			void loadDirectly();
			void loadIntoCamera(nw4r::g3d::Camera cam);

			void setSomeVars(bool isCentered, float m40, float m44, float width, float height); // 802D1500

			Info *getStructContainingInfo(); // 802D1AB0

			void doSomethingWithAPassedMatrix(Mtx m, float f1, float f2, float f3, float f4); // 802D1B40

		//protected:
			void copyAllFields(Screen &s); // 802D1430
			void setParent(Screen *pParent = 0); // 802D1540

			void useScreenWidth640(); // 802D15A0
			void calculateCrap(); // 802D15D0

			bool checkIfFlag1IsSet(); // 802D1B10


			Screen *parent; // I think it's the parent screen, anyway ...
			float _40, _44, _48, _4C, _50, _54;
			Info info;
	};


	class LookAtCamera /* : public BaseCamera */ {
		public:
			virtual Mtx *getMatrix();
			virtual Mtx *getMatrixAgain();
			virtual void callCalculateMatrix();
			virtual void calculateMatrix();
			virtual void loadMatricesIntoGX();
			virtual void _vf1C(); // null
			virtual Vec getCamPos();
			virtual void doStuffInvolvingVfsAndOtherObject(void *unkType);
			virtual void _vf28(); // null
			virtual Mtx *getPreviousMatrix();

			void assignToNW4RCamera(nw4r::g3d::Camera &cam); // 802BEB70
			Vec getStuffFromMatrix(); // 802BEBC0
			Vec getMoreStuffFromMatrix(); // 802BEC20
			Vec getEvenMoreStuffFromMatrix(); // 802BEC80

		private:
			Mtx matrix;
			Mtx previousMatrix;

		public:
			Vec camPos, target, camUp;
	};

	class ProjectOrtho /* : public something? */ {
		public:
			virtual u32 getProjectionType();
			virtual void setGXProjection();
			virtual void _vf10(); // null
			virtual VEC2 _vf14(VEC2 *something);
			virtual Vec _vf18(float something, /*BaseCamera?*/ LookAtCamera *camera);
			virtual Vec _vf1C(float something, /*BaseCamera?*/ LookAtCamera *camera);
			virtual Vec _vf20(VEC2 *something);
			virtual void _vf24();
			virtual void setOrthoOntoCamera(nw4r::g3d::Camera &cam);
			virtual void _vf2C(); // null
			virtual void setGXProjectionUnscaled(); // does not take aspect ratio into account

			ProjectOrtho(); // 802BF6C0
			void setVolume(float top, float bottom, float left, float right); // 802BF710
			void setDefaults(); // I think? 802BF830

			Mtx44 matrix; // unused? dunno
			void *_44; // dunno type
			float near, far, top, bottom, left, right;
	};
}


class TileRenderer {
public:
	TileRenderer();
	~TileRenderer();

	TileRenderer *previous, *next;
	u16 tileNumber;
	u8 unkFlag, someBool;
	float x, y, z;
	float scale;
	s16 rotation;
	u8 unkByte;

	u16 getTileNum();
	bool getSomeBool();
	void setSomeBool(u8 value);
	
	float getX();
	float getY();
	float getZ();
	void setPosition(float x, float y);
	void setPosition(float x, float y, float z);

	u8 getUnkFlag();

	void setVars(float scale); // sets unkFlag=1, rotation=0, unkByte=0
	void setVars(float scale, s16 rotation); // sets unkFlag=2, unkByte=0
	
	float getScale();
	float getRotationFloat();
	s16 getRotation();

	u8 getUnkByte();

	class List {
	public:
		u32 count;
		TileRenderer *first, *last; // order?

		void add(TileRenderer *r);
		void remove(TileRenderer *r);
		void removeAll();

		List();
		~List();
	};
};

class dActor_c; // forward declaration
class dStageActor_c; // forward declaration

#include <collision/solidcollider.h>
#include <collision/hitboxcollider.h>
#include <actor/stageactor.h>

#include <statelib.h>

#include <game/statewrapper.h>


#include <linklist.h>
#include <tree.h>
#include <functionchain.h>




class dStageActor_c;	// forward declaration

#include <collision/sensor.h>
#include <collision/collidermgr.h>

#include <collision/basiccollider.h>
#include <collision/solidontopcollider.h>
#include <collision/rideableactorcollider.h>


class freezeMgr_c {
public:
	u32 some_count;
	u32 ice_timer1;
	u32 ice_timer2;
	u32 _mstate;				//0=not,1=frozen,3=die_coin
	u32 _10;
	u32 _nstate;				//1=countdown,2=meltedNormal
	u32 spawns_coin;			//1=delete,3=coin
	u32 _1C_timerLenType;
	u32 _20_defaultTimerLenType;
	u32 _24;
	u32 _28;
	u32 perm_freeze;
	u32 _30;
	u32 actorIds[12];
	void* owner;		// _64

	freezeMgr_c();
	~freezeMgr_c();
	//FIXME add params and returns
	void doSomethingCool1();
	void doSomethingCool2();
	void setSomething(u32,u32,u32);
	bool Create_ICEACTORs(void*,int);
	void Delete_ICEACTORs();
	void SetIceTimer_pt1();
	void SetIceTimer_pt2();
	void CheckIceTimer_lte_Value();
	void doSomethingCool3();
	void doSomethingCool4();
	void doSomethingCool5();
	void doSomethingCool6();
	void DoMeltNormal();
	void doSomethingCool7();
	void CheckCountdownTimer();
};


class StageActorLight {
public:
	
	virtual void init(void *allocator, int);
	virtual void update();
	virtual void draw();
	// virtual ~StageActorLight();

	Vec pos;
	float size;
	u32 secondClass;
	u32 firstClass;
};

#include <game/base/base.h>
#include <actor/actor.h>


class dPlayerInput_c {
	public:
		dPlayerInput_c();
		~dPlayerInput_c();

		void activate(int playerID) { this->playerID = playerID; }
		void deactivate(); // 8005E030

		void execute(); // 8005E040
		void loadDataDirectlyFromRemocon(); // 8005E2B0

		bool detectGroundPound(); // 8005E300

		enum Flags {
			NO_INPUT = 0,
			FORCE_TWO_ON = 3,
			FORCE_TWO_OFF = 4,
			ONLY_HOLD_RIGHT = 6,
			FORCE_VALUES = 7,
			NO_SHAKING = 8,
		};
		enum FlagMask {
			NO_INPUT_MASK = 1 << NO_INPUT,
			FORCE_TWO_ON_MASK = 1 << FORCE_TWO_ON,
			FORCE_TWO_OFF_MASK = 1 << FORCE_TWO_OFF,
			ONLY_HOLD_RIGHT_MASK = 1 << ONLY_HOLD_RIGHT,
			FORCE_VALUES_MASK = 1 << FORCE_VALUES,
			NO_SHAKING_MASK = 1 << NO_SHAKING,
		};

		void setFlag(Flags flag); // 8005E3B0
		void unsetFlag(Flags flag); // 8005E460

		void clearInputs(); // 8005E480
		void unsetLeftAndRight(); // 8005E4A0

		u32 getPressedA(); // 8005E4C0
		u32 getAllHeldArrows(); // 8005E4D0
		u32 getAllPressedArrows(); // 8005E4E0

		u32 getHeldUp(); // 8005E4F0
		u32 getHeldDown(); // 8005E500
		u32 getHeldLeft(); // 8005E510
		u32 getHeldRight(); // 8005E520
		u32 getPressedUp(); // 8005E530
		u32 getPressedDown(); // 8005E540
		u32 getPressedLeft(); // 8005E550
		u32 getPressedRight(); // 8005E560

		u32 getPressedTwo(); // 8005E570
		u32 getHeldTwo(); // 8005E580

		u32 getPressedBorOne(); // 8005E590
		u32 getHeldBorOne(); // 8005E5D0

		u32 getHeldOne(); // 8005E610

		u32 willPunchFence_maybe(); // 8005E620
		u32 willEatOrSpit_maybe(); // 8005E630
		u32 willPerformSomeAction_B_or_One(); // 8005E680
		u32 willShootProjectile(); // 8005E690

		u32 j_getPressedTwo(); // 8005E6E0

		u32 willJump_maybe(); // 8005E6F0

		u32 getHeldTwoModifiedByFlags(); // 8005E740

		u32 yetAnotherTwoThunk(); // 8005E770

		u32 areWeShaking(); // 8005E780
		void clearShakeInputs(); // 8005E790

		bool getLRMovementDirection(int *pOutDirection = 0); // 8005E7A0

		u32 anotherDownAction(); // 8005E830

		u32 isDownPressedExclusively(); // 8005E840
		u32 isUpPressedWithoutLeftOrRight(); // 8005E890

		bool wasTwoPressedRecently(); // 8005E8B0

		void setPermanentForcedButtons(u32 buttons); // 8005E910
		void unsetPermanentForcedButtons(u32 buttons); // 8005E930
		void setTransientForcedButtons(u32 buttons); // 8005E960
		void forceShakingOn(); // 8005E980

	private:
		int playerID;
		u16 heldButtons, nowPressed;
		u16 lastHeldButtons, lastNowPressed;
		u16 permanentForcedButtons, transientForcedButtons;
		u16 forcedShakeValue;
		u16 flags;

		u8 gpCounter;
		bool dontResetGPValuesNextTick, gpActive;
		u8 shaking1, shaking2;
		bool wasActionExecuted;
		int countdownAfterFlag6Deactivated;
		u32 _20;
		int rollingHistoryOfTwo[4][10];
		int rollingHistoryOfTwoModifiedByFlags[4][10];
};


#include <actor/player.h>
#include <actor/multistateactor.h>


struct EntityDeathInfo {
	float xSpeed, ySpeed, maxYSpeed, yAccel;
	dStateBase_c *state;
	u32 _14, _18;
	u8 _1C, _1D, isDead;
};

#include <actor/entityactor.h>
#include <actor/blockactor.h>




class daKameckDemo : public dEn_c {

public:
	USING_STATES(daKameckDemo);
	REF_NINTENDO_STATE(DemoWait);
	REF_NINTENDO_STATE(DemoSt);
	REF_NINTENDO_STATE(DemoSt2);
};


class daBossKoopa_c : public dEn_c {

public:
	USING_STATES(daBossKoopa_c);
	REF_NINTENDO_STATE(Fall);
};

class daNeedles : public dEn_c {

public:
	USING_STATES(daNeedles);
	REF_NINTENDO_STATE(DemoWait);
	REF_NINTENDO_STATE(DemoAwake);
	REF_NINTENDO_STATE(Idle);
	REF_NINTENDO_STATE(Die);
};

struct dWaterInfo_s {
	float x, y, z, width, height;
	int isInUse;
	u8 type, layer;
};

class dWaterManager_c {
	private:
		dWaterInfo_s blocks[80];
	public:
		float current;

		static dWaterManager_c *instance;

		dWaterManager_c() { instance = this; }
		~dWaterManager_c() { instance = 0; }

		void setup();
		int addBlock(dWaterInfo_s *block);

	private: // ?
		int isPointWithinSpecifiedBlock(VEC2 *pos, int blockID);
		int getAngleOfVector(VEC2 *vec);
		int isPointWithinBubbleInternal(VEC2 *pos, int blockID, VEC2 *pOutVec, float *pFloat, s16 *pShort);

	public:
		int queryPosition(VEC2 *pos, VEC2 *pOutBlockPos, float *pOutFloat, s16 *pOutAngle, int layer);
		int isPositionWithinBubble(VEC2 *pos, VEC2 *pOutBlockPos, int blockID, int layer);
		void removeBlock(int blockID);
		void setPosition(VEC3 *pos, int blockID);
		void setGeometry(VEC3 *pos, float width, float height, int blockID);
};

class BgGmBase : public dBase_c {
public:
	struct something_s {
		u16 x, y;
		int layer, countdown, tile;
	};
	struct limitLineEntry_s {
		float leftX, rightX;
		float _8, _C, _10, y, _18, _1C, _20, _24, _28, _2C;
		float zoneY, zoneHeight, zoneX, zoneWidth;
		u16 flags; // documented in idb struct, kind of
	};
	struct manualZoomEntry_s {
		float x1, x2, y1, y2;
		u8 unkValue6, zoomLevel, firstFlag;
	};
	struct beets_s {
		float _0, _4;
		u8 _8;
	};

	u32 behaviours; //type?

	int somethingCount;
	something_s somethings[256];

	// Limit lines grouped by:
	// 64 zones; 8 groups IDed by mysterious setting; 16 lines per group
	limitLineEntry_s limitLines[64][8][16];

	manualZoomEntry_s manualZooms[64];

	u32 _8F478, _8F47C;

	beets_s beets1[100];
	beets_s beets2[100];
	// TODO, a lot

	u16 *getPointerToTile(int x, int y, int layer, int *pBlockNum = 0, bool unused = false);

	// Note: these tile numbers are kinda weird and involve GetTileFromTileTable
	void placeTile(u16 x, u16 y, int layer, int tile);

	void makeSplash(float x, float y, int type); // 80078410
};


class dBgGm_c : public BgGmBase {
public:
	// TODO TODO TODO TODO TODO
	static dBgGm_c *instance;

	TileRenderer::List *getTileRendererList(int index);
};


class dPlayerModelBase_c {
	// dunno what's public and what's private here
	// don't really care
public:
	dPlayerModelBase_c(u8 player_id);		// 800D5420
	virtual ~dPlayerModelBase_c();			// 800D55D0

	mHeapAllocator_c allocator;
	u32 _20;
	u32 _24;
	char someAnimation[2][0x38]; // actually PlayerAnim's
	char yetAnotherAnimation[40]; // actually m3d::banm_c afaics -- is it even 40 bytes?
	Vec HeadPos; // maybe not an array
	Vec HatPos; // maybe not an array
	Mtx finalMatrix;
	Mtx firstMatrix;
	Vec headOffs;
	Vec pos;
	u8 player_id_1;
	u8 player_id_2;
	u8 powerup_id;
	u8 powerup_tex;
	int current_anim;
	int last_anim_maybe;
	u32 _15C;
	int someFlags;
	u32 _164;
	u32 _168; // related to jump_strings
	u32 _16C;
	u32 _170;
	u32 _174;
	u8 _178;
	char padding[3]; // not needed?
	u32 model_visibility_flags_maybe; // 0x100=star glow, 0x200=star effects
	u32 mode_maybe;
	float _184;
	float _188;
	u32 _18C;
	char someArray[6][12]; // some unknown class/struct
	char _1D8[0x24];
	short _1FC;
	short _1FE;
	short _200;
	char padding_[2]; // not needed?
	u32 _204;
	u32 _208;

	class ModelThing {
		public:
			m3d::mdl_c body, head;
	};

	virtual int _vf0C();						// 800D6DA0
	virtual void prepare();					// 800D5720
	virtual void finaliseModel();				// 800D5740
	virtual void update();						// 800D5750
	virtual void update3DStuff();				// 800D5760
	virtual void _vf20();						// 800D6D90
	virtual void draw();						// 800D5C70
	virtual ModelThing *getCurrentModel();				// 800D5870
	virtual int getCurrentResFile();			// 800D62D0
	virtual void setPowerup(u8 powerup_id);	// 800D5730
	virtual void setPowerupTexture();			// 800D5CC0
	virtual void _vf38();						// 800D6D80
	virtual void _vf3C();						// 800BD750
	virtual void enableStarColours();			// 800D6D70
	virtual void disableStarColours();			// 800D6D60
	virtual void enableStarEffects();			// 800BD740
	virtual void disableStarEffects();			// 800BD730
	virtual void getModelMatrix(u32 unk, Mtx *dest);	// 800D5820
	virtual int _vf54();						// 80318D0C
	virtual bool _vf58(int type, char *buf, bool unk); // 800D6930
	virtual void startAnimation(int id, float updateRate, float unk, float frame);	// 800D5EC0
	virtual int _vf60();						// 800D6920
	virtual void _vf64(int id, float unk1, float unk2, float unk3); // 800D62F0
	virtual void _vf68(int id, float unk);		// 800D63E0
	virtual void _vf6C();						// 800D62E0
	virtual void _vf70();						// 800D6690
	virtual void _vf74();						// 800D66A0
	virtual void _vf78();						// 800D66B0
	virtual void SomethingRelatedToPenguinAnims();	// 800D66C0
	virtual void _vf80();						// 800D6A20
	virtual void _vf84(float frame);			// 800D5D00
	virtual void _vf88(float frame);			// 800D5D70
	virtual void _vf8C(float updateRate);		// 800D5D80
	virtual void setUpdateRateForAnim1(float updateRate);	// 800D5DF0
	virtual void _vf94();						// 800D6D40
	virtual int _vf98();						// 800D6D30
	virtual void _vf9C();						// 800D6D20
	virtual int _vfA0();						// 800D6D10
	virtual void _vfA4();						// 800D6D00
	virtual int _vfA8();						// 800D6CF0
	virtual void _vfAC(bool blah);						// 800BD720

	// I won't even bother with non-virtual functions....
};


class dPlayerModel_c : public dPlayerModelBase_c {
	public:
		// methods? what do you need those for...
		// (not bothering with them either)
		nw4r::g3d::ResFile modelResFile, animResFile1, animResFile2;

		u8 effectClass0[296];
		u8 effectClass1[296];

		ModelThing models[4];

		// maybe these are mAllocator_c?
		m3d::anmTexPat_c bodySwitchAnim;
		m3d::anmClr_c bodyStarAnmClr;
		m3d::anmTexPat_c headSwitchAnim;
		m3d::anmTexPat_c propHeadSwitchAnim;
		m3d::anmTexPat_c pengHeadSwitchAnim;
		m3d::anmClr_c headStarAnmClr;

		u32 currentPlayerModelID;
		u32 lastPlayerModelID;
		// tons of crap more, don't feel like fixing this up atm
};


class dPlayerModelHandler_c {
public:
	dPlayerModelHandler_c(u8 player_id);	// 800D6DB0
	virtual ~dPlayerModelHandler_c();		// 800D6EF0

	dPlayerModelBase_c *mdlClass;	// might be dPlayerModel_c ?

	int loadModel(u8 player_id, int powerup_id, int unk);	// 800D6EE0
	void update();											// 800D6F80
	void setMatrix(Mtx *matrix);								// 800D6FA0
	void setSRT(Vec position, S16Vec rotation, Vec scale);	// 800D7030
	void callVF20();										// 800D70F0
	void draw();											// 800D7110

private:
	int hasMatrix;	// might be bool ?

	void allocPlayerClass(u8 player_id);					// 800D6E00
};


class mTexture_c {
public:
	mTexture_c();	// 802C0D20
	mTexture_c(u16 width, u16 height, u32 format);	// 802C0D70

	// vtable is at 80350450
	virtual ~mTexture_c();	// 802C0DB0
	virtual void setFlagTo1();	// 802C0E20

	void setImageBuffer(void *buffer);	// 802C0E30
	void load(u32 id);			// 802C0E50
	void makeTexObj(GXTexObj *obj);		// 802C0E90
	void flushDC();						// 802C0F10

	void makeRadialGradient();			// 802C0F60 parameters unknown yet
	void makeLinearGradient(int type, char size, u16 startPos, u16 endPos,
			GXColor begin, GXColor end, bool startAtCenter);	// 802C1120
	// "type" should be enum once I figure it out
	// reverse might not be accurate

	void allocateBuffer(/* EGG::Heap */void *heap = 0);	// 802C14D0

	void plotPixel(u16 x, u16 y, GXColor pixel);	// 802C1570

	void *getBuffer() const { return buffer; }

	u16 width;
	u16 height;
	u8 flags;
	u8 format;
	u8 wrapS;
	u8 wrapT;
	u8 minFilter;
	u8 magFilter;

private:
	void *buffer;
	void *myBuffer;
};


class dDvdLoader_c {
public:
	dDvdLoader_c();				// 8008F140
	virtual ~dDvdLoader_c();	// 8008F170

	void *load(const char *filename, u8 unk = 0, void *heap = 0);	// 8008F1B0

	bool close();	// 8008F2B0 -- Frees command, DON'T USE THIS unless you free the buffer yourself
	bool unload();	// 8008F310 -- Frees command and buffer, USE THIS

	int size;
	void *command;	// really mDvd_toMainRam_c
	void *heap;		// really EGG::Heap
	void *buffer;

private:
	virtual void freeBuffer();	// 8008F380
	void freeCommand();			// 8008F3F0
};



namespace nw4r {
	namespace ut {
		class CharWriter {
			public:
				CharWriter();
				~CharWriter();

				void SetupGX();

				void SetFontSize(float w, float h);
				void SetFontSize(float v);
				float GetFontWidth() const;
				float GetFontHeight() const;
				float GetFontAscent() const;
				float GetFontDescent() const;

				// returns width
				float Print(ushort character);

				void PrintGlyph(float, float, float, /* nw4r::ut::Glyph const & */ void*);

				void UpdateVertexColor();

			private:
				void SetupGXWithColorMapping(Color c1, Color c2);

			public:
				Color minColMapping, maxColMapping;
				Color vtxColours[4];
				Color topColour, bottomColour;

				u32 modeOfSomeKind;
				float scaleX;
				float scaleY;
				float posX;
				float posY;
				float posZ;
				u32 minFilt;
				u32 magFilt;
				u16 completelyUnknown;
				u8 alpha;
				u8 isFixedWidth;
				float fixedWidthValue;
				/* ResFont* */ void *font;
		};

		// actually TextWriterBase<w>, but ...
		class TextWriter : public CharWriter {
			public:
				TextWriter();
				~TextWriter();

				float GetLineHeight() const;

				// left out most of these to avoid all the format string vararg bullshit
				float CalcStringWidth(wchar_t const *string, int length) const;

				float Print(wchar_t const *string, int length);
				
				float CalcLineWidth(wchar_t const *string, int length);

				float GetLineSpace() const;

				bool IsDrawFlagSet(ulong, ulong) const;

				float widthLimit;
				float charSpace;
				float lineSpace;
				u32 tabWidth;
				u32 drawFlag;
				void *tagProcessor;
		};
	}
}

// More layout crap
// This file REALLY needs to be reorganised.

namespace nw4r {
namespace lyt {

	class ResourceAccessor {
	public:
		ResourceAccessor();
		virtual ~ResourceAccessor();

		virtual void *GetResource(u32 dirKey, const char *filename, u32 *sizePtr) = 0;
		virtual void *GetFont(const char *name);
	};

	class ArcResourceAccessor : public ResourceAccessor {
	public:
		ArcResourceAccessor();
		~ArcResourceAccessor();

		bool Attach(void *data, const char *rootDirName);
		void *GetResource(u32 dirKey, const char *filename, u32 *sizePtr);
		void *GetFont(const char *name);

		char arcHandle[0x1C]; // should be a struct, but I'm too lazy to reverse it >_>
		u32 unk_20;
		ut::LinkList list; // 0x24
		char rootDirName[0x80]; // 0x30
		// class ends at 0xB0
	};

	class AnimResource {
		public:
			void *fileHeader;
			void *info;
			void *tags;
			void *share;
	};

}
}

namespace m2d {
	class ResAcc_c {
	public:
		ResAcc_c();
		virtual ~ResAcc_c();
		virtual void initialSetup();

		nw4r::lyt::ResourceAccessor *resAccPtr; // 0x04
		void *arcData; // 0x08
		nw4r::lyt::ArcResourceAccessor resAcc; // 0x0C
		// class ends at 0xBC

		bool attachArc(void *data, const char *rootDir); // 0x801637A0
	};

	class ResAccLoader_c : public ResAcc_c {
	public:
		ResAccLoader_c();
		~ResAccLoader_c();

		void *buffer;
		dDvdLoader_c loader; // 0xC0
		// ends at 0xD4

		bool loadArc(const char *path);
		bool loadArc(const char *path, u8 unk);
		void free();
	};

	class AnmResHandler_c {
		public:
			AnmResHandler_c();
			virtual ~AnmResHandler_c();

			struct Thing {
				nw4r::lyt::Group *group;
				nw4r::lyt::AnimTransform *animTransform;
			};

			nw4r::lyt::AnimResource resource; // 0x04
			Thing *groups; // 0x14
			u32 groupCount; // 0x18

			bool load(const char *name, ResAcc_c *resAcc, nw4r::lyt::Layout *layout, bool useDiffInit);
			bool free();
			Thing *getThingForGroupName(const char *name); // 80164130
	};

	class FrameCtrl_c {
		public:
			virtual ~FrameCtrl_c();

			float frameCount; // 0x04
			float currentFrame; // 0x08
			float lastFrame; // 0x0C
			float speed; // 0x10; default: 1
			u8 flags; // 0x14
			
			void processAnim(); // 0x80163800
			void setup(u8 flags, float frameCount, float speed, float initialFrame); // 0x801638A0
			void setCurrentFrame(float frame); // 0x80163910
			void setSpeed(float speed); // 0x80163920
			bool isDone(); // 0x80163930
	};

	class Anm_c {
		public:
			FrameCtrl_c *frameCtrlPtr;

			AnmResHandler_c *resHandler; // ? 0x04
			AnmResHandler_c::Thing *thing; // 0x08
			u8 flags; // 0x0C - |1 = enabled successfully?

			FrameCtrl_c frameCtrl; // 0x10

			// too lazy to list the methods for this atm
			// after IDA reverted all the changes I made to the DB this
			// afternoon ...
	};

	class EmbedLayoutBase_c : public Base_c {
	public:
		EmbedLayoutBase_c();
		~EmbedLayoutBase_c();

		void draw(); // don't call this directly

		virtual void update();
		virtual bool build(const char *brlytPath, ResAcc_c *resAcc = 0);

		nw4r::lyt::Pane *getRootPane();
		nw4r::lyt::Pane *findPaneByName(const char *name) const;
		nw4r::lyt::TextBox *findTextBoxByName(const char *name) const;
		nw4r::lyt::Picture *findPictureByName(const char *name) const;
		nw4r::lyt::Pane *findWindowByName(const char *name) const;

		void animate();
		void calculateMtx();

		nw4r::lyt::Layout layout; // 0x10 -- actually m2d::Layout_c but I'll add that later
		nw4r::lyt::DrawInfo drawInfo; // 0x30
		ResAcc_c *resAccPtr; // 0x84 -- a ResAcc? referenced in Build()
		float posX; // 0x88
		float posY; // 0x8C
		float clipX; // 0x90
		float clipY; // 0x94
		float clipWidth; // 0x98
		float clipHeight; // 0x9C
		bool clippingEnabled; // 0xA0
		u32 hasAnimations; // 0xA4
		u32 unk_A8; // 0xA8
	};

	class EmbedLayout_c : public EmbedLayoutBase_c {
	public:
		EmbedLayout_c();
		~EmbedLayout_c();

		bool build(const char *brlytPath, ResAcc_c *resAcc = 0);

		bool loadArc(const char *name, bool isLangSpecific);
		bool loadArc(const char *name, u8 unk, bool isLangSpecific);

		bool loadArcForRegion(const char *name); // uses EU/Layout/$name

		// there's also a NedEU one, but should it really be listed here...?

		bool free();

		// does NSMBW even use consts? I have no idea. maybe not

		void getPanes(const char **names, nw4r::lyt::Pane **output, int count) const;
		void getWindows(const char **names, nw4r::lyt::Pane **output, int count) const; // TODO: change to others
		void getPictures(const char **names, nw4r::lyt::Picture **output, int count) const;
		void getTextBoxes(const char **names, nw4r::lyt::TextBox **output, int count) const;

		void setLangStrings(const char **names, const int *msgIDs, int category, int count);

		void loadAnimations(const char **names, int count);
		void loadGroups(const char **names, const int *animLinkIDs, int count);

		void enableNonLoopAnim(int num, bool goToLastFrame = false);
		void enableLoopAnim(int num);
		void resetAnim(int num, bool goToLastFrame = false);
		void disableAnim(int num);
		void disableAllAnimations();

		bool isAnimOn(int num = -1);
		bool isAnyAnimOn();

		void execAnimations();

		ResAccLoader_c loader; // 0xAC
		AnmResHandler_c *brlanHandlers; // 0x180
		Anm_c *grpHandlers; // 0x184
		bool *animsEnabled; // 0x188
		int brlanCount; // 0x18C
		int grpCount; // 0x190
		int lastAnimTouched; // 0x194

	private:
		void fixTextBoxesRecursively(nw4r::lyt::Pane *pane);
	};
}


extern "C" float fmod(float, float);
bool RectanglesOverlap(Vec *bl1, Vec *tr1, Vec *bl2, Vec *tr2);


/* Tilemap related stuff */
class TilemapClass {
	public:
		virtual ~TilemapClass();

		u16 *allocatedBlocks[256];
		u32 _404;

		u8 blockLookup[2048];
		
		u16 blockCount;

		u32 _C0C;
		u32 ts1ID, ts2ID, ts3ID, layerID, areaID, frmHeap, is2Castle;

		// Only the public API is listed
		u16 *getPointerToTile(int x, int y, u32 *blockNum = 0, bool unkBool = 0);
		// TODO: more?
};

class BGDatClass {
	public:
		BGDatClass();
		virtual ~BGDatClass();

		u8 *bgData[4][3];
		TilemapClass *tilemaps[4][3];
		u8 *tsObjIndexData[4][4];
		u8 *tsObjData[4][4];
		char tsNames[4][4][0x20];
		// this is fucked up!
		// the parent heap is frmHeaps[0][0]
		// each tileset's heap is frmHeaps[AREA][LAYER+1]
		void *frmHeaps[4][4];

		static BGDatClass *instance; // 8042A0D0

		// I've only listed the public API because other stuff isn't really needed atm.
		const char *getTilesetName(int area, int number);
		// TODO: more?
};

struct BGRender {
	u8 unk[0xC00];
	u8 *objectData;
	u8 _C04, _C05;
	u16 _C06, _C08;
	u16 blockNumber;
	u16 curX, curY;
	u16 tileToPlace;
	u16 objDataOffset, objType, objX, objY, objWidth, objHeight;
	u16 tileNumberWithinBlock, areaID;
};

void randomiseNormalTerrain(TilemapClass*, BGRender*, int);
void randomiseSubTerrain(TilemapClass*, BGRender*, int);
void randomiseNohara(TilemapClass*, BGRender*, int);
void randomiseSabaku(TilemapClass*, BGRender*, int);
void randomiseGake(TilemapClass*, BGRender*, int);
void randomiseKaigan(TilemapClass*, BGRender*, int);
void randomiseDoukutu(TilemapClass*, BGRender*, int);
void randomiseShiroBoss1(TilemapClass*, BGRender*, int);
void randomiseObake(TilemapClass*, BGRender*, int);
void randomiseObakeSoto(TilemapClass*, BGRender*, int);
void randomiseKoriChika(TilemapClass*, BGRender*, int);
void randomisePa2Kori(TilemapClass*, BGRender*, int);

// A HACK
extern void *DVDClass;
extern "C" u8 *GetRes(void *Something, const char *arcname, const char *filename);

// Use THESE instead, until I write something up for dRes or dRes_c or whatever the fuck it's called

inline u8 *getResource(const char *arcName, const char *fileName) {
	return GetRes((void*)(((u8*)DVDClass)+4), arcName, fileName);
}

inline void scaleDown(Vec* scale, float amt) { scale->x -= amt; scale->y -= amt; scale->z -= amt; }
inline void scaleUp(Vec* scale, float amt) { scale->x -= amt; scale->y -= amt; scale->z -= amt; }


void ConvertStagePositionToScreenPosition(Vec2 *screen, Vec *stage);


class SoundPlayingClass /* : public something */ {
public:
	// Size: 0x17C
	
	void PlaySoundAtPosition(int id, Vec2 *pos, u32 flags); // 80198D70
	
	static SoundPlayingClass *instance1; // 8042A03C
	static SoundPlayingClass *instance2; // 8042A03C
	static SoundPlayingClass *instance3; // 8042A03C
};


class dEffectBreakBase_c {
	// TODO (not really needed, though)
};

class dEffectBreakMgr_c {
	public:
		static dEffectBreakMgr_c *instance;

		dEffectBreakMgr_c();
		~dEffectBreakMgr_c();

		void execute();
		void draw();

		bool spawnTile(Vec *position, u32 settings, char param);
		// Settings:
		// (BlockType << 8) | (HalfSpeedFlag << 4) | (VelocityChange & 3)
		// 
		// Types:
		// 0=Brick, 1=Stone, 2=Wood, 3=Question, 4=Used
		// 5=Red, 6=Used, 7=Unused, 8=Final Battle

		bool spawnIcePiece(Vec *position, u32 settings, char param);

		// Three more still need to be REed

	private:
		bool prepare(dEffectBreakBase_c *ef, Vec *pos, u32 settings, u8 param);
		void cleanup();
		void cleanupAll();
};

namespace EGG {
	class Effect7C {
		public:
			virtual ~Effect7C();
			virtual void clear();

			u8 data[0x94];
	};

	class Effect {
		public:
			Effect(); // 802D7D90
			virtual ~Effect();

			char effectName[32];
			u32 secondVarFromSpawnFunc;
			u32 flags; // 1 = has translation, 2 = matrix was set, 4 = ?

			float _2C, _30, _34;
			Vec translate;
			Mtx matrix;

			u32 HandleBase_00, HandleBase_04;

			Effect7C ef7C;

			virtual bool _vf0C();
			virtual void _vf10(); // related to RetireEmitterAll?
			virtual void _vf14(); // also related to RetireEmitterAll?
			virtual void _vf18(); // related to RetireEmitterAll and RetireParticleAll?
			virtual void _vf1C(bool flag); // sets or clears some flag
			virtual void _vf20(bool flag); // sets or clears another flag
			virtual void _vf24(bool flag); // sets or clears both of those flags

			// all these functions have a strange purpose
			// _vf54 is the one sole exception to everything written below!
			//
			// they all call through to ef7C methods, which modify two bitfields stored in it:
			// void EGG::Effect7C::modifyBitfields(u32 mask, u32 flagBit) {
			//     if (flagBit & 1)
			//         this->_04 |= mask;
			//     else
			//         this->_04 &= ~mask;
			//     if (flagBit & 2)
			//         this->_08 |= mask;
			//     else
			//         this->_08 &= ~mask;
			// }
			// after that, the methods set value(s) passed by the caller
			virtual void _vf28(u16 unk, u32 flagBit);		// flag is 1, value stored to its 0xC
			virtual void _vf2C(float unk, u32 flagBit);		// flag is 2, value stored to its 0x10
			virtual void _vf30(u16 unk, u32 flagBit);		// flag is 4, value stored to its 0x14
			virtual void _vf34(u16 unk, u32 flagBit);		// flag is 8, value stored to its 0x16
			virtual void _vf38(char unk, u32 flagBit);		// flag is 0x10, value stored to its 0x18
			virtual void _vf3C(float unk, u32 flagBit);		// flag is 0x20, value stored to its 0x1C
			virtual void _vf40(float unk, u32 flagBit);		// flag is 0x40, value stored to its 0x20
			virtual void _vf44(float unk, u32 flagBit);		// flag is 0x80, value stored to its 0x24
			virtual void _vf48(float unk, u32 flagBit);		// flag is 0x100, value stored to its 0x28
			virtual void _vf4C(Vec *unk, u32 flagBit);		// flag is 0x200, values stored at its 0x2C
			virtual void _vf50(Vec *unk, u32 flagBit);		// flag is 0x400, values stored at its 0x38
			virtual void _vf54(Vec *unk);
			virtual void _vf58(u8 r, u8 g, u8 b, u8 a, u32 flagBit);	// flag is 0x1000, value stored to its 0x44

			// this one is similar, but it stores two colours into an array at 0x48
			// alpha values are ignored
			// valid indices are 0 and 1 afaics?
			// flag is 0x2000 << index (so, 0x2000 or 0x4000)
			virtual void _vf5C(GXColor one, GXColor two, int index, u32 flagBit);

			// this one sets the alpha for those colours
			// flag is 0x8000 or 0x10000
			virtual void _vf60(u8 one, u8 two, int index, u32 flagBit);

			virtual void _vf64(Vec2 *vec, u32 flagBit);		// flag is 0x20000, values stored at its 0x58
			virtual void _vf68(Vec2 *vec, u32 flagBit);		// flag is 0x40000, values stored at its 0x60
			virtual void _vf6C(Vec *vec, u32 flagBit);		// flag is 0x80000, values stored at its 0x68
			virtual void _vf70(Vec *vec, u32 flagBit);		// flag is 0x100000, values stored at its 0x74

			// a bit of a special case: this one will set/clear 0x10000000 depending on flagBit
			// but it'll also set 0x20000000 if anotherFlag is true
			// if anotherFlag is false, it'll clear 0x20000000 even if flagBit is set
			// values stored at ef7C's 0x80
			virtual void _vf74(Vec *vec, bool anotherFlag, u32 flagBit);

			virtual void _vf78(Vec *vec, u32 flagBit);		// flag is 0x40000000, values stored at its 0x8C

			virtual void _vf7C(Vec *one, Vec2 *two=0); // sets transformation vals and calls vf68

			// stores to _2C, _30, _34
			virtual void setXformValsFromParams(float one, float two, float three);
			virtual void setXformValsFromVEC3(Vec *vec);

			virtual void setTranslationFromVEC3(Vec *vec);
			virtual void setMatrix(Mtx *mtx);

			virtual void _vf90(/* ??? */); // absolutely zero idea what this does

			virtual void makeItHappen(); // for internal use?

			virtual void clear(); // resets all properties, etc
	};
}

namespace mEf {
	class effect_c : public EGG::Effect {
		public:
			~effect_c();

			void clear();

			virtual bool probablyCreateWithName(const char *name, u32 unk);
			virtual bool spawn(const char *name, u32 unk, const Vec *pos=0, const S16Vec *rot=0, const Vec *scale=0);
			virtual bool spawnWithMatrix(const char *name, u32 unk, const Mtx *mtx);

			// these two deal with mEf::effectCB_c and crap. absolutely no idea.
			virtual bool _vfA8(/* tons and tons of params */);
			virtual bool _vfAC(/* a slightly smaller amount of params */);

			virtual bool _vfB0(const Vec *pos=0, const S16Vec *rot=0, const Vec *scale=0);
			virtual bool _vfB4(const Mtx *mtx);
	};

	class es2 : public effect_c {
		public:
			// vtable: 80329CA0
			~es2();

			void _vf10();
			void _vf18();

			void makeItHappen();
			bool probablyCreateWithName(const char *name, u32 unk);
			bool spawn(const char *name, u32 unk, const Vec *pos=0, const S16Vec *rot=0, const Vec *scale=0);
			bool spawnWithMatrix(const char *name, u32 unk, const Mtx *mtx);
			bool _vfB0(const Vec *pos=0, const S16Vec *rot=0, const Vec *scale=0);
			bool _vfB4(const Mtx *mtx);

			virtual u8 returnField11D(); // does exactly what it says on the tin

			u32 _114, _118;
			u8 _11C, _11D;
			u32 _120, _124;
	};
}

struct SSM { short width, height; float xScale, yScale; };
extern SSM ScreenSizesAndMultipliers[3];
extern int currentScreenSizeID;

extern float GlobalScreenWidth, GlobalScreenHeight;

void DoSceneChange(u16 name, u32 sceneSettings, u32 unk);

extern u32 GlobalTickCount;

// A hack, imported from tilesetfixer.cpp
extern void *BGDatClass, *StagePtr;
inline int GetZoneNum() {
	char *st = (char*)StagePtr;
	return st[0x120F];
}
inline int GetAreaNum() {
	char *st = (char*)StagePtr;
	return st[0x120E];
}

inline u8 *GetStaffCreditScore() {
	char *thing = ((char*)StagePtr) + 0x11FC;
	return *((u8**)thing);
}



class ClassWithCameraInfo {
	public:
		ClassWithCameraInfo();
		virtual ~ClassWithCameraInfo();

		// Not quite sure what this is for, stores bitflags for each tile or something?
		void initBitfields();
		void deinitBitfields();
		void deleteOneBitfield(int area, int layer);

		u16 getBitfieldPart(int area, u16 entryIndex, int layer);
		void setBitfieldPart(int area, u16 entryIndex, int layer, u16 value);


		void setSomeInitialVars();

		void s_80082180(); // sets initedTo2 to 0, 1 or 2 depending on the X position
		void s_800821E0(); // same thing for field_81

		float getEffectiveScreenLeft(); // takes wrap into account


		u16 *tileBitfields[12];
		float _34, screenLeft, screenTop, screenWidth, screenHeight;
		float screenCentreX, screenCentreY;

		float _50, _54, _58, _5C, _60, _64, _68, _6C, _70, _74;
		float xOffset, yOffsetForTagScroll;

		u8 initedTo2, _81;
		u32 _84, _88, _8C, _90;
		void *bgHeap;


		static ClassWithCameraInfo *instance;

		// That is all
};


namespace mHeap {
	extern void *archiveHeap;
	extern void *commandHeap;
	extern void *dylinkHeap;
	extern void *assertHeap;
	extern void *gameHeaps[3];
};

void WriteNumberToTextBox(int *number, const int *fieldLength, nw4r::lyt::TextBox *textBox, bool unk); // 800B3B60
void WriteNumberToTextBox(int *number, nw4r::lyt::TextBox *textBox, bool unk); // 800B3BE0

namespace EGG {
	class MsgRes {
		private:
			const u8 *bmg, *INF1, *DAT1, *STR1, *MID1, *FLW1, *FLI1;
		public:
			MsgRes(const u8 *bmgFile, u32 unusedParam); // 802D7970
			virtual ~MsgRes();

			static void parseFormatCode(wchar_t initialTag, const wchar_t *string, u8 *outArgsSize, u32 *outCmd, const wchar_t **args); // 802D7B10

			const wchar_t *findStringForMessageID(int category, int message) const; // 0x802D7B50

		private:
			void setBMG(const u8 *ptr); // 802D7B90
			void setINF(const u8 *ptr); // 802D7BA0
			void setDAT(const u8 *ptr); // 802D7BB0
			void setSTR(const u8 *ptr); // 802D7BC0
			void setMID(const u8 *ptr); // 802D7BD0
			void setFLW(const u8 *ptr); // 802D7BE0
			void setFLI(const u8 *ptr); // 802D7BF0
			int identifySectionByMagic(u32 magic) const; // 802D7C00

		protected:
			struct INFEntry {
				u32 stringOffset;
			};
			const INFEntry *findINFForMessageID(int category, int message) const; // 802D7C90
			u32 getEntryFromMID(int index) const; // 802D7D70
	};
}
namespace dScript {
	class Res_c : public EGG::MsgRes {
		public:
			Res_c(const u8 *bmgFile, u32 unusedParam); // 800CE7F0
			~Res_c();

			u16 getCharScaleForMessageID(int category, int message) const; // 800CE890
			u8 getFontIDForMessageID(int category, int message) const; // 800CE8C0
	};
}
class MessageClass {
	public:
		dDvdLoader_c loader;
		void *rawBmgPointer;
		dScript::Res_c *msgRes;
};

dScript::Res_c *GetBMG(); // 800CDD50
void WriteBMGToTextBox(nw4r::lyt::TextBox *textBox, dScript::Res_c *res, int category, int message, int argCount, ...); // 0x800C9B50

extern "C" dAc_Py_c* GetSpecificPlayerActor(int number);
extern "C" dStageActor_c *CreateActor(u16 classID, int settings, Vec pos, char rot, char layer);
extern "C" dStageActor_c *Actor_SearchByID(u32 actorID);

struct DoSomethingCool {
	u32 unk_01; //0000
	Vec3 pos;  //0004
	Vec3 scale; //0010
	f32 unk_02; //001C
	f32 unk_03; //0020
	f32 unk_04; //0024
	f32 unk_05; //0028
	f32 unk_06; //002C
	f32 unk_07; //0030
	f32 unk_08; //0034
	f32 unk_09; //0038
};

struct IceActorSpawnInfo {
	// fuck that, we don't actually need it
	//~IceActorSpawnInfo();
	u32 flags;
	Vec3 pos, scale;
	f32 what[8];
};

extern "C" u8 dSprite_c__getXDirectionOfFurthestPlayerRelativeToVEC3(dEn_c *, Vec pos);
extern "C" void *ShakeScreen(void *, unsigned int, unsigned int, unsigned int, unsigned int);
extern "C" void *PlaySoundAsync(dStageActor_c *, int soundID);
extern "C" u32 GetActivePlayerCount();

#include "newer.h"

class BGGMEffectRenderer : public m3d::proc_c {
	private:
		u32 effectGroupID;
	public:
		~BGGMEffectRenderer();
		void drawOpa();
		void drawXlu();
		virtual bool setupEffectRenderer(mAllocator_c *allocator, int opaPrio, int xluPrio, int groupID);
};

void CleanUpEffectThings();
bool FreeEffects(int efNum);
bool FreeBreff(int efNum);
bool FreeBreft(int efNum);


// a bad hack
extern "C" void Pause__Q44nw4r3snd6detail10BasicSoundFbi(void *_this, bool pause, int count);
extern "C" void Stop__Q44nw4r3snd6detail10BasicSoundFi(void *_this, int unk);
extern "C" void StrmSound_SetTrackVolume(void *_this, u32 mask, int count, float value);
extern "C" void SetPitch__Q44nw4r3snd6detail10BasicSoundFf(void *_this, float value);
extern "C" void SetVolume__Q44nw4r3snd6detail10BasicSoundFfi(void *_this, float value, int count);

namespace nw4r {
	namespace snd {
		class SoundHandle {
			protected:
				void *data;
			public:
				SoundHandle() { data = 0; }
				~SoundHandle() { DetachSound(); }

				bool Exists() { return (data != 0); }
				void Stop(int unk) { Stop__Q44nw4r3snd6detail10BasicSoundFi(data, unk); }

				void SetPitch(float value) { SetPitch__Q44nw4r3snd6detail10BasicSoundFf(data, value); }
				void Pause(bool pause, int count) { Pause__Q44nw4r3snd6detail10BasicSoundFbi(data, pause, count); }

				void SetVolume(float value, int count) { SetVolume__Q44nw4r3snd6detail10BasicSoundFfi(data, value, count); }

				void *GetSound() const { return data; }

				void DetachSound();
		};

		class StrmSoundHandle : public SoundHandle {
			public:
				void SetTrackVolume(u32 mask, int count, float value) { StrmSound_SetTrackVolume(data, mask, count, value); }
		};
	}
}

extern "C" nw4r::snd::SoundHandle *PlaySound(dStageActor_c *, int soundID);

extern float EnemyBounceValue;

class dStockItemShadow_c : public dBase_c {
	public:
	m2d::EmbedLayout_c layout;

	nw4r::lyt::Pane *rootPane;
	nw4r::lyt::TextBox *textBoxes[14];
	nw4r::lyt::Picture *buttonBases[7];
	bool layoutLoaded, visible, needsUpdate;
	int values[8];
	nw4r::lyt::TextBox *hammerValue, *hammerX;
	nw4r::lyt::Picture *hammerButtonBase;
};

class dStockItem_c : public dBase_c {
	public:
	int onCreate();
	int onDelete();
	int beforeExecute();
	int onExecute();
	int onDraw();

	dStockItem_c();
	~dStockItem_c();


	u32 _70;
	m2d::EmbedLayout_c layout;
	dStateWrapper_c<dStockItem_c> state;

	nw4r::lyt::Pane
		*rootPane,
		*N_forUse_PPos[4],
		*N_icon[7],
		*N_stockItem, *N_stockItem_01,
		*N_itemSelect_00;

	nw4r::lyt::Picture
		*P_icon[7],
		*P_buttonBase[7],
		*P_iconBase[10];

	/*da2DPlayer_c*/void *player2d[4];
	/*daWMItem_c*/void *itemPtr[7];
	dStockItemShadow_c *shadow;
	int actionTaken;
	u32 _318, _31C, _320, _324;
	int usedItem;
	EGG::Effect effectArray[4], oneEffect;
	int effectIDs[4];
	int selectedItem, previousItem;
	u32 _8A8, _8AC;
	int playerCount, counts[7];
	u32 _8D0;
	int someAnimID;
	bool isPlayerActive[4], layoutLoaded, show, _8DE;

	/*daWMItem_c*/void *newItemPtr[8];
	int newCounts[8];
	nw4r::lyt::Picture *newButtonBase[8];
	nw4r::lyt::Pane *newIconPanes[8];
	nw4r::lyt::Picture *newIconPictures[8];

	void setScalesOfSomeThings();
	int getIconPictureIDforPlayer(int i);
};

class dYesNoWindow_c : public dBase_c {
	public:
		int onCreate();
		int onDelete();
		int onExecute();
		int onDraw();

		dYesNoWindow_c();
		~dYesNoWindow_c();

		m2d::EmbedLayout_c layout;
		dStateWrapper_c<dYesNoWindow_c> state;

		nw4r::lyt::Pane *rootPane;

		nw4r::lyt::Picture
			*P_yesBase_00, *P_noBase_00, *P_centerBase_00;

		nw4r::lyt::TextBox
			*T_questionS_00, *T_question_00,
			*T_otehonTextS_01, *T_otehonText_01,
			*T_needCoinX_00, *T_needcoin_00,
			*T_yes_00, *T_yes_01,
			*T_no_00, *T_no_01;

		nw4r::lyt::Pane *N_otehonText_00, *N_saveIcon_00;

		int current, previous, type, starCoinRequiredCount;
		bool layoutLoaded, visible, close, animationActive, keepOpen, cancelled, hasBG;
};


class daBossDemo_c;
class StageE4 {
	public:
		u8 ___[0x14];
		daBossDemo_c *currentBossDemo;
		// NOT COMPLETE
		static StageE4 *instance;

		void killAllEnemiesAtLevelEnd(int type);
		// 0=normal, 1=?, 2=kill indiscriminately, for ambush levels
		// just use 0.
		void spawnCoinJump(const VEC3 &pos, int direction, int coinCount, int layer);
};

// Some ugly code
extern void *SelectCursorPointer;
extern "C" void UpdateSelectCursor(nw4r::lyt::Pane *pane, int whichOne, bool unkBool);
extern "C" void HideSelectCursor(void *scPtr, int whichOne);

typedef int (*__Player_VF3D4_type)(void*);
inline int Player_VF3D4(void *self) {
	VF_BEGIN(__Player_VF3D4_type, self, 245, 0x60)
		return VF_CALL(self);
	VF_END;
}

extern "C" void PlaySoundWithFunctionB4(void *src, nw4r::snd::SoundHandle *handle, int id, int unk);
extern "C" bool CheckIfPlayingSound(void *src, int id);
extern void *SoundRelatedClass;

void GetPosForLayoutEffect(VEC3 *pos, bool quack);

bool SmoothRotation(s16 *pValue, s16 target, s16 stepSize);


struct PlayerAnimState {
	const char *regularAnim, *rideAnim, *yoshiAnim, *penguinAnim;
	int playsOnce;
	float _14, _18;
	u32 _1C, flags;
};
extern PlayerAnimState PlayerAnimStates[177];


class daEnBossKoopaDemoPeach_c : public dEn_c {
	public:
		mHeapAllocator_c allocator;
		int stage;
		nw4r::g3d::ResFile resFile;
		m3d::mdl_c model;
		m3d::anmChr_c chrAnm;
		m3d::anmTexPat_c patAnm;
		u8 _mysteryData[0x38];
		int counter;
		u16 _628;
		float _62C;
		u32 cageID;
		bool dontCallYet;
		mEf::es2 effects[1];


		int onCreate();
		int onDelete();
		int onExecute();
		int onDraw();

		daEnBossKoopaDemoPeach_c();
		~daEnBossKoopaDemoPeach_c();

		Vec2 _vf70();

		virtual void beginState_Wait();
		virtual void executeState_Wait();
		virtual void endState_Wait();
		virtual void beginState_Call();
		virtual void executeState_Call();
		virtual void endState_Call();
		virtual void beginState_Turn();
		virtual void executeState_Turn();
		virtual void endState_Turn();
		virtual void beginState_Open();
		virtual void executeState_Open();
		virtual void endState_Open();
		virtual void beginState_Rescue();
		virtual void executeState_Rescue();
		virtual void endState_Rescue();
		virtual void beginState_Thank();
		virtual void executeState_Thank();
		virtual void endState_Thank();

		REF_NINTENDO_STATE(Wait);
		REF_NINTENDO_STATE(Call);
		REF_NINTENDO_STATE(Turn);
		REF_NINTENDO_STATE(Open);
		REF_NINTENDO_STATE(Rescue);
		REF_NINTENDO_STATE(Thank);
};

class dStageActorMgr_c {
	public:
		int depthCounter1, depthCounter2, depthCounter3, depthCounter4;

		u16 storedShorts[1000];
		u8 storedBytes[1000];

		u16 _BC8;
		bool _BCA, dontRunThings;
		u32 lastScreenLeft, lastScreenTop, _BD4, _BD8;

		static dStageActorMgr_c *instance;
};

class daBossDemo_c : public dActorState_c {
	public:
		int onCreate();
		int onDelete();
		int onExecute();
		int onDraw();
		void willBeDeleted();

		int counter;
		u32 _3D4, idOfOtherActor;

		virtual void beginState_Ready();
		virtual void executeState_Ready();
		virtual void endState_Ready();
		virtual void beginState_BattleStDemo();
		virtual void executeState_BattleStDemo();
		virtual void endState_BattleStDemo();
		virtual void beginState_BattleIn();
		virtual void executeState_BattleIn();
		virtual void endState_BattleIn();
		virtual void beginState_BattleEdDemo();
		virtual void executeState_BattleEdDemo();
		virtual void endState_BattleEdDemo();

		virtual bool beatLevel();
		virtual void exitLevel();

		virtual void beginSomething() { }
		virtual void endSomething() { }

		virtual u32 getIdOfOtherActor() { return idOfOtherActor; }
		virtual void setIdOfOtherActor(int id) { idOfOtherActor = id; }

		virtual bool vf128() { return false; }
		virtual u32 justReturnField3D4_decidesIfEndBattle() { return _3D4; }
		virtual bool vf130() { return true; }

		virtual dStageActor_c *getActorPointerForSomething() { return 0; }

		virtual void init();

		USING_STATES(daBossDemo_c);
		REF_NINTENDO_STATE(Ready);
		REF_NINTENDO_STATE(BattleStDemo);
		REF_NINTENDO_STATE(BattleIn);
		REF_NINTENDO_STATE(BattleEdDemo);
};

class BalloonRelatedClass {
	public:
		static BalloonRelatedClass *instance;

		u32 ___[0x20];
		u32 _20;
};

class Stage80 {
	public:
		static Stage80 *instance;

		float acparamb1, acparambptr, acparamb2, acparamb3, acparamb4;
		float acparam1, acparamptr, acparam2, acparam3, acparam4;
		float screenXOffset, screenYOffset;
		u32 someFlag; // &1 = dEn_c::add2ToYSpeed(), &2 = pow, &4 = mpgp
		u32 _34;
		u8 _38, _39;
		int lengthOfPow, lengthOfMPGP;
};

class dTheEnd_c : public dBase_c {
	public:
		m2d::EmbedLayout_c layout;
		dStateWrapper_c<dTheEnd_c> state;

		nw4r::lyt::Pane *rootPane;

		bool layoutLoaded, willShow, willHide, animationPlaying;
};
inline dTheEnd_c *GetTheEnd() {
	char *thing = ((char*)StagePtr) + 0x1200;
	return *((dTheEnd_c**)thing);
}

extern void *_8042A788;
extern "C" void sub_8019C390(void *, int);
extern "C" bool SpawnEffect(const char*, int, Vec*, S16Vec*, Vec*);

class StageC4 {
	public:
		static StageC4 *instance;

		virtual ~StageC4();

		// Not gonna bother with listing methods here
		int stageNum, selection, playerNum;
		u32 _10, _14;
		u8 flags, _19, _1A, willDisplay, _1C, _1D;
};

#endif

