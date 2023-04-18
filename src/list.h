#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>  // true, false

// Linked list node.
typedef struct node
{
	int x;
	int y;
	struct node* next;

} node;

node* node_push_back(node* root, int x, int y)
{
	// Create new node and initialize point.
	node* const new_node = malloc(sizeof(node));
	new_node->x = x;
	new_node->y = y;
	new_node->next = NULL;

	// Find last node in linked list.
	while (root->next)
		root = root->next;

	// Tell last node to reference new node.
	root->next = new_node;

	// Return new node.
	return new_node;
}

node* node_push_front(node* root, int x, int y)
{
	// Create new node and initialize point.
	node* const new_node = malloc(sizeof(node));
	new_node->x = x;
	new_node->y = y;
	new_node->next = root;

	// Return new node.
	return new_node;
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

int node_count(node* root)
{
	int size = 1;
	while ((root = root->next))
		size++;
	return size;
}

#endif
