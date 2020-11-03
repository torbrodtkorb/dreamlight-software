/* Copyright (C) Tor Brodtkorb */

#ifndef LIST_H
#define LIST_H

#include "types.h"

struct list_node {
	struct list_node* next;
	struct list_node* prev;	
};

#define list_get_entry(node, type, member) \
		((type)*)(u8*)(offsetof((type), (member))) \
	

struct thread {
	
};




#endif
