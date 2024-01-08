#ifndef SENSOR_H
#define SENSOR_H
#include <common.h>

enum SensorFlags {
	SENSOR_POINT = 0,
	SENSOR_LINE = 1,

	SENSOR_TYPE_MASK = 1,
	SENSOR_2 = 2, // has not shown up yet...?
	SENSOR_IGNORE_SIMPLE_COLL = 4,
	SENSOR_8 = 8, // can enter pipe?
	SENSOR_10 = 0x10, // Related to ice
	SENSOR_20 = 0x20, // related to ice, too
	SENSOR_40 = 0x40, // checked by simplecollider
	SENSOR_80 = 0x80, // checked by simplecollider
	SENSOR_100 = 0x100, // checked by simplecollider
	SENSOR_200 = 0x200, // checked by simplecollider
	SENSOR_400 = 0x400, // checked by simplecollider
	SENSOR_800 = 0x800, // checked by simplecollider
	SENSOR_NO_QUICKSAND = 0x1000,
	SENSOR_2000 = 0x2000, // something to do with fences maybe?
	SENSOR_BREAK_BLOCK = 0x4000,
	SENSOR_8000 = 0x8000, // used
	SENSOR_10000 = 0x10000, // used
	SENSOR_COIN_1 = 0x20000,
	SENSOR_COIN_2 = 0x40000,
	SENSOR_COIN_OUTLINE = 0x80000,
	SENSOR_ACTIVATE_QUESTION = 0x100000,
	SENSOR_ACTIVATE_DONUTS = 0x200000,
	SENSOR_HIT_BRICK = 0x400000,
	SENSOR_BREAK_BRICK = 0x800000,
	SENSOR_HIT_OR_BREAK_BRICK = 0xC00000,
	SENSOR_1000000 = 0x1000000, // has not shown up yet...?
	SENSOR_2000000 = 0x2000000, // corresponds to SCF_400?
	SENSOR_4000000 = 0x4000000, // something related to hitting blocks 
	SENSOR_8000000 = 0x8000000, // corresponds to SCF_20?
	SENSOR_10000000 = 0x10000000, // used
	SENSOR_20000000 = 0x20000000, // used
	SENSOR_40000000 = 0x40000000, // used
	SENSOR_80000000 = 0x80000000, // used
};

// Output is split into...
// Above   :
// FC000000: 11111100000000000000000000000000
// Below   :
//  3FFE000:       11111111111110000000000000
//   1FE000:            111111110000000000000
//    18000:                11000000000000000
// Adjacent:
//     1FFF:                    1111111111111

enum SensorOutputFlags {
	CSOUT_ABOVE_ALL = 0xFC000000,
	CSOUT_BELOW_ALL = 0x3FFE000,
	CSOUT_ADJACENT_ALL = 0x1FFF,
};

// 0x8000 : Has object from Class 2DC?
// 0x4000 : Has slope from Class 2DC?

struct hLine_s {
	float x1, x2, y;
};
struct vLine_s {
	float x, y1, y2;
};

struct pointSensor_s;
struct lineSensor_s;
struct sensorBase_s {
	u32 flags;
	inline pointSensor_s *asPoint() const {
		return (pointSensor_s*)this;
	}
	inline lineSensor_s *asLine() const {
		return (lineSensor_s*)this;
	}
};
struct pointSensor_s : sensorBase_s {
	inline pointSensor_s() { }
	inline pointSensor_s(s32 _x, s32 _y) {
		x = _x; y = _y;
	}
	inline pointSensor_s(u32 _flags, s32 _x, s32 _y) {
		flags = _flags | SENSOR_POINT;
		x = _x; y = _y;
	}
	s32 x, y;
};
struct lineSensor_s : sensorBase_s {
	inline lineSensor_s() { }
	inline lineSensor_s(s32 _a, s32 _b, s32 _d) {
		flags = SENSOR_LINE;
		lineA = _a; lineB = _b;
		distanceFromCenter = _d;
	}
	inline lineSensor_s(u32 _flags, s32 _a, s32 _b, s32 _d) {
		flags = _flags | SENSOR_LINE;
		lineA = _a; lineB = _b;
		distanceFromCenter = _d;
	}
	s32 lineA, lineB, distanceFromCenter;
};
#endif