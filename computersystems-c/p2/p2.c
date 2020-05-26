#include <stdio.h>
#include <sys/mman.h>
#include <malloc.h>

typedef enum
{
	true=1, false=0
} bool;

void* region;
int used;

struct Block {
	void* ptr;
	int size;
	struct Block *next;
};

struct Block *freeList;
struct Block *allocatedListRoot;
struct Block *lastAllocated;
struct Block *findFreeBlock(int num_bytes_to_allocate);


void heap_init(int num_pages_for_heap) {

	int regionSize = 4096 * num_pages_for_heap;

	region = mmap(NULL, regionSize, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	
	freeList = (struct Block *) malloc(sizeof(struct Block));
	freeList->size = regionSize;
	freeList->next = NULL;
	freeList->ptr = region;
	//printf("region: %x\n", region);

	allocatedListRoot = (struct Block *) malloc(sizeof(struct Block));
	lastAllocated = allocatedListRoot;
}

void* heap_alloc(int num_bytes_to_allocate) {
	num_bytes_to_allocate = (num_bytes_to_allocate%16) + num_bytes_to_allocate;
	
	struct Block *freeB = findFreeBlock(num_bytes_to_allocate);
	if (freeB==NULL) {
		//printf("freeB is NULL!\n");
		return NULL;
	}

	void* free = freeB->ptr;

	if (freeB->size > num_bytes_to_allocate) {
		freeB->ptr += num_bytes_to_allocate;
		freeB->size -= num_bytes_to_allocate;
	}
	
	struct Block *allocated = (struct Block *) malloc(sizeof(struct Block));
	allocated->next = NULL;
	allocated->size = num_bytes_to_allocate;
	allocated->ptr = free;

	lastAllocated->next = allocated;
	lastAllocated = allocated;

	//printf("free: %x\n", free);
	return free;

}

struct Block* findAllocatedFromPointer(void* pointer_to_area_to_free, struct Block **prev) { //prev being the previous item in the search
	struct Block *found = NULL;
	struct Block *block = allocatedListRoot->next;
	while (found==NULL) {
		if (block->ptr == pointer_to_area_to_free) {
			found = block;
		} else {
			
			if (block->next != NULL) {
				*prev = block;
				block = block->next;
			} else {
				break;
			}
		}

	}
	return found;
}

void joinAdjacentFrees() {
	
	int i=0;
	struct Block *current = freeList;
	while (current->next != NULL) {
		if (current->ptr + current->size == current->next->ptr) {
			struct Block *next = current->next;
			current->size += next->size;
			current->next = next->next;
			next->ptr = NULL;
			next->size = 0;
			next->next = NULL;
			free(next);
			i+=1;

		
		}
		current = current->next;
	}
	if (i>0) {
		joinAdjacentFrees(); 
	}

}

void heap_free(void* pointer_to_area_to_free) {
	struct Block *prev = allocatedListRoot;
	struct Block *found = findAllocatedFromPointer(pointer_to_area_to_free, &prev);
	if (found!= NULL) {
		struct Block *next = found->next;

		if (lastAllocated == found) {
			lastAllocated = prev;
		}
		if (next!=NULL) {
			prev->next = next;
		} else {
			prev->next = NULL;
		}
	
		if (freeList->ptr > found->ptr) {
			found->next = freeList;
			freeList = found;
		} else {
			found->next = NULL;
			struct Block *current = freeList;
			prev = freeList;
			int f = 0;
			while (f==0) {
				if (current->next == NULL) {
					prev->next = found;
					f = 1;
				} else {

					current = current->next;
					if (found->ptr > prev->ptr && found->ptr < current->ptr) {
						found->next = current;
						prev->next = found;
						f = 1;//break
					} else {
						prev = current;
					}

				}


			}
			
		}

	}
	joinAdjacentFrees();

}

struct Block* findFreeBlock(int num_bytes_to_allocate) {
	struct Block *found = NULL;
	struct Block *block = freeList;
	while (found==NULL) {

		////printf("block size: %d, ptr: %x, next: %x\n", block->size, block->ptr, block->next);
		////printf("num_bytes_to_allocate: %d\n", num_bytes_to_allocate);
		if (block->size >= num_bytes_to_allocate) {
			found = block;
		} else {
			if (block->next != NULL) {
				block = block->next;
			} else {
				break;
			}
		}
	}
	return found;
}

