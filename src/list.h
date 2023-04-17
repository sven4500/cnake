#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>  // true, false

// Linked list node.
typedef struct node_
{
	int x;
	int y;
	struct node_* next;

} node;

node* node_push_back(node* root, int x, int y)
{
	// Create new node and initialize point.
	node* n = malloc(sizeof(node));
	n->x = x;
	n->y = y;
	n->next = NULL;

	// Find last node in linked list.
	while (root->next)
		root = root->next;

	// Tell last node to reference new node.
	root->next = n;

	// Return new node.
	return n;
}

node* node_push_front(node* root, node* n)
{
	node* next = root->next;
	root->next = n;
	n->next = next;
	return n;
}

void node_pop_back(node* root)
{
	node* prev = root;
	node* last = root;

	// Find last node in linked list.
	while (last->next) {
		prev = last;
		last = last->next;
	}

	prev->next = NULL;
	free(last);
}

node* node_contains(node* root, int x, int y)
{
	if (!root)
		return NULL;
	do
	{
		if (root->x == x && root->y == y)
			return root;
	} while ((root = root->next));
	return NULL;
}

int node_size(node* root)
{
	int size = 1;
	while ((root = root->next))
		size++;
	return size;
}

#endif
