#ifndef FUNCTION_CHAIN_H
#define FUNCTION_CHAIN_H
#include <common.h>
typedef bool (*ChainedFunc)(void*);

class FunctionChain {
public:
	ChainedFunc *functions;
	u16 count;
	u16 current;

	void setup(ChainedFunc *functions, u16 count); // 8015F740
};

#endif