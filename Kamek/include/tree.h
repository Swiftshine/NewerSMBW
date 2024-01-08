#ifndef TREE_H
#define TREE_H


struct TreeNode {
	TreeNode *parent;
	TreeNode *child;
	TreeNode *prev;
	TreeNode *next;
	void *owned_obj;
};


struct Tree {
	TreeNode *firstNode;
	// PTMF goes here, but I don't know how to represent it
};

#endif