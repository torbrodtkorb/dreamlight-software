#include "gmalloc.h"
#include "print.h"
#include <stddef.h>

/// Allocate data for the malloc allocator
static u8 malloc_buffer[250000];
static struct slob_struct malloc_struct;

void gmalloc_init(void)
{
	slob_init(&malloc_struct, (u32)malloc_buffer, (u32)malloc_buffer + sizeof(malloc_buffer));
}

void* gmalloc(u32 size)
{
	return slob_alloc(size, &malloc_struct);	
}

void gfree(void* ptr)
{
	slob_free(ptr, &malloc_struct);
}

/// Gets the total number of bytes used
u32 slob_get_used(struct slob_struct* slob)
{
	return slob->stats.used;
}

u32 gmalloc_used(void)
{
	return slob_get_used(&malloc_struct);
}

/// Initialized the SLOB allocator. The zone must be setup correctly
u8 slob_init(struct slob_struct* slob, u32 start, u32 stop)
{
	slob->start_addr = start;
	slob->end_addr = stop;

	// Sanity check
	if (slob->start_addr > slob->end_addr) {
		return 0;
	}

	// Align the start and stop address to MM_ALIGN
	if (slob->start_addr & (SLOB_ALIGN - 1)) {
		slob->start_addr += SLOB_ALIGN;
		slob->start_addr &= ~(SLOB_ALIGN - 1);
	}
	if (slob->end_addr & (SLOB_ALIGN - 1)) {
		slob->end_addr &= ~(SLOB_ALIGN - 1);
	}

	// Make the first and last node
	struct slob_node* tmp_node = (struct slob_node *)slob->start_addr;
	slob->last_node = (struct slob_node *)slob->end_addr -
	sizeof(struct slob_node);

	// Setup the links and the size fields
	slob->node.size = 0;
	slob->node.next = tmp_node;
	slob->first_node = &slob->node;

	tmp_node->size = (u8 *)slob->last_node - (u8 *)slob->first_node;
	tmp_node->next = slob->last_node;

	slob->last_node->next = NULL;
	slob->last_node->size = 0;

	// Update the mm stats
	slob->stats.total = tmp_node->size;
	slob->stats.used = 0;

	return 1;
}

/// The `first` node is the node which is pointing to the first physical node in
/// the memory. The `last` is the last node pointing to NULL.
static u8 slob_insert_free(struct slob_node* first, struct slob_node* last,
struct slob_node* node)
{
	struct slob_node* it;

	for (it = first; it; it = it->next) {
		if ((u32)it->next > (u32)node) {
			break;
		}
	}
	if (it == NULL) {
		return 0;
	}

	// The `it` is pointing to the mm_node before the node to insert
	u32 addr = (u32)it;
	if ((addr + it->size) == (u32)node) {
		// Backward merge
		it->size += node->size;
		node = it;
	}

	addr = (u32)node;
	if ((addr + node->size) == (u32)it->next) {
		if (it->next != last) {
			// Forward merge
			node->size += it->next->size;
			node->next = it->next->next;
			} else {
			// If backward merge this does not do anything
			node->next = it->next;
		}
		} else {
		// If backboard merge this does not do anything
		node->next = it->next;
	}

	if (node != it) {
		it->next = node;
	}
	return 1;
}

/// Allocates a physically and virtually continuous memory region. This is based
/// on the SLOB allocator (simple list of block)
void* slob_alloc(u32 size, struct slob_struct* slob)
{
	if (size == 0) {
		return NULL;
	}

	size += sizeof(struct slob_node);

	// Align the size
	if (size & (SLOB_ALIGN - 1)) {
		size += SLOB_ALIGN;
		size &= ~(SLOB_ALIGN - 1);
	}

	struct slob_node* it_prev = slob->first_node;
	struct slob_node* it = it_prev->next;

	while (it) {
		if (it->size >= size) {
			break;
		}
		it_prev = it;
		it = it->next;
	}
	if (it == NULL) {
		// We are out of memory
		return NULL;
	}

	// Remove the current node from the list
	it_prev->next = it->next;

	// We have to check if the memory block is large enough to contain more data
	u32 new_size = it->size - size;
	if (new_size >= SLOB_MIN_BLOCK) {
		/// We have more space, and the space is large enough to contain at least
		/// MM_MIN_BLOCK number of bytes
		struct slob_node* new = (struct slob_node *)((u32)it + size);

		// The kmalloc_insert_free requires the size field to be set
		new->size = new_size;
		slob_insert_free(slob->first_node, slob->last_node, new);
		} else {
		size = it->size;
	}

	// Size is holding the number of bytes to be allocated
	slob->stats.used += size;
	it->size = size;
	it->next =(struct slob_node *)0xC0DEBABE;
	
	return (void *)((u32)it + sizeof(struct slob_node));
}

/// Frees a pointer allocated by slob_alloc
void slob_free(void* ptr, struct slob_struct* slob)
{
	if (ptr == NULL) {
		while (1);
	}
	struct slob_node* free = (struct slob_node *)((u32)ptr - sizeof(struct slob_node));

	// Check if the kmalloc tracks this pointer
	if ((u32)free->next != 0xC0DEBABE) {
		while (1);
	}

	// Range check
	if (((u32)free < (u32)slob->first_node) ||
	((u32)free >= (u32)slob->last_node)) {
		while (1);
	}

	slob->stats.used -= free->size;
	slob_insert_free(slob->first_node, slob->last_node, free);
}
