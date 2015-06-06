#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct node {
	int rec;
	int key;
	node *next;

	node(int r, int k, node *n)
		: rec(r)
		, key(k)
		, next(n)
	{}
};

#endif LINKED_LIST_H