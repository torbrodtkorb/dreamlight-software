/* Copyright (C) Tor Brodtkorb */

#ifndef LIST_H
#define LIST_H

#include "types.h"
#include <stddef.h>

struct list_node {
	struct list_node* next;
	struct list_node* prev;	
};

static inline void list_init(struct list_node* list)
{
	list->next = list;
	list->prev = list;
}

static inline void list_insert(struct list_node* node, struct list_node* prev, struct list_node* next)
{
	prev->next = node;
	node->next = next;
	node->prev = prev;
	next->prev = node;
}

static inline void list_insert_first(struct list_node* node, struct list_node* list)
{
	list_insert(node, list, list->next);
}

static inline void list_insert_last(struct list_node* node, struct list_node* list)
{
	list_insert(node, list->prev, list);
}


#define list_get_entry(node, type, member) \
	(type*)((u8*)(node) - offsetof(type, member))

#define list_iterate(node_ptr, list) \
	for (node_ptr = (list)->next; (node_ptr) != (list); node_ptr = (node_ptr)->next)






#endif
