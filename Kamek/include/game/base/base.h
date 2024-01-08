#ifndef BASE_H
#define BASE_H
#include <common.h>
#include <linklist.h>
#include <tree.h>
#include <functionchain.h>

class fBase_c {
public:
	u32 id;
	u32 settings;
	u16 name;
	u8 _A;
	u8 _B;
	u8 _C;
	u8 _D;
	u8 base_type;
	u8 _F;
	TreeNode link_connect;
	OrderedLinkListEntry link_execute;
	OrderedLinkListEntry link_draw;
	LinkListEntry link_IDlookup;
	u32 _50;
	u32 _54;
	u32 _58;
	u32 heap;

	fBase_c();

	virtual int onCreate();
	virtual int beforeCreate();
	virtual int afterCreate(int);

	virtual int onDelete();
	virtual int beforeDelete();
	virtual int afterDelete(int);

	virtual int onExecute();
	virtual int beforeExecute();
	virtual int afterExecute(int);

	virtual int onDraw();
	virtual int beforeDraw();
	virtual int afterDraw(int);

	virtual void willBeDeleted();

	virtual bool moreHeapShit(u32 size, void *parentHeap);
	virtual bool createHeap(u32 size, void *parentHeap);
	virtual void heapCreated();

	virtual ~fBase_c();

	void Delete();

	fBase_c *GetParent();
	fBase_c *GetChild();
	fBase_c *GetNext();

	bool hasUninitialisedProcesses();	// 80162B60
	fBase_c *findNextUninitialisedProcess();

	static fBase_c *search(Actors name, fBase_c *previous = 0);
	static fBase_c *search(u32 id);
	static fBase_c *searchByBaseType(int type, fBase_c *previous);
};

class dBase_c : public fBase_c {
public:
	u32 _64;
	const char *explanation_string;
	const char *name_string;

	dBase_c();

	int beforeCreate();
	int afterCreate(int);
	int beforeDelete();
	int afterDelete(int);
	int beforeExecute();
	int afterExecute(int);
	int beforeDraw();
	int afterDraw(int);

	~dBase_c();

	virtual const char *GetExplanationString();
};

class dScene_c : public dBase_c {
public:
	FunctionChain *ptrToInitChain;

	dScene_c();

	int beforeCreate();
	int afterCreate(int);
	int beforeDelete();
	int afterDelete(int);
	int beforeExecute();
	int afterExecute(int);
	int beforeDraw();
	int afterDraw(int);

	~dScene_c();


	void setInitChain(FunctionChain &initChain) {
		ptrToInitChain = &initChain;
	}
};

#endif