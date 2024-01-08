#ifndef LINK_LIST_H
#define LINK_LIST_H

struct LinkListEntry {
	LinkListEntry *prev;
	LinkListEntry *next;
	void *owned_obj;
};


struct LinkList {
	LinkListEntry *first;
	LinkListEntry *last;
	// PTMF goes here, but I don't know how to represent it
};


struct OrderedLinkListEntry : LinkListEntry {
	u16 order;
	u16 _;
};

#endif