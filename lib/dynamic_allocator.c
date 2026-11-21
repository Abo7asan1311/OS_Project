/*
 * dynamic_allocator.c
 *
 *  Created on: Sep 21, 2023
 *      Author: HP
 */
#include <inc/assert.h>
#include <inc/string.h>
#include "../inc/dynamic_allocator.h"

/************************************************************************************/
//==================================================================================//
//============================== GIVEN FUNCTIONS ===================================//
//==================================================================================//
//TODO: [PROJECT'26.GM#1] DYNAMIC ALLOCATOR - [0] GIVEN FUNCTIONS
//==================================
// [1] INITIALIZE BUDDY FREE LISTS:
//==================================
void buddy_init()
{
	//panic("buddy_init is not implemented yet");

	for (int l = BUDDY_LOWER_LEVEL; l <= BUDDY_UPPER_LEVEL; ++l)
	{
		LIST_INIT(&(freeBlockLists[l]));
	}
}
//====================================
// [2] PRINT SIZE OF FREE LISTS:
//====================================
void PrintFreeBlockLists()
{
	for (int i = BUDDY_LOWER_LEVEL; i <= BUDDY_UPPER_LEVEL; ++i)
	{
		cprintf("Level#%d: %d\n", i, LIST_SIZE(&freeBlockLists[i]));
	}
}
/************************************************************************************/

//==================================================================================//
//============================ REQUIRED FUNCTIONS ==================================//
//==================================================================================//
//===========================
// [1] GET BLOCK SIZE:
//===========================
__inline__ uint32 get_block_size(void *va)
{
	//TODO: [PROJECT'26.GM#1] DYNAMIC ALLOCATOR - [1] get_block_size
	//Your code is here
	int ret;

	struct BlockMetaData *meta = (struct BlockMetaData *)((char *)va - META_DATA_SIZE);
	ret =BLOCK_SIZE(meta->level);

	cprintf("the size of the block at location %x is %d", va, ret);

return ret;

}
//===========================
// [2] ALLOCATE BLOCK:
//===========================
void *alloc_block(uint32 requiredSize)
{

	uint32 act_size = requiredSize + META_DATA_SIZE;
	uint32 target_lvl = 0;
	struct BlockList *block_ptr = freeBlockLists + BUDDY_LOWER_LEVEL;
	int size = LIST_SIZE(block_ptr);
	int i, j;

	if(act_size > DYN_ALLOC_MIN_BLOCK_SIZE && act_size < DYN_ALLOC_MAX_BLOCK_SIZE)
	{
		/* find the target lvl */
		for(i = BUDDY_LOWER_LEVEL; i < BUDDY_UPPER_LEVEL; i++)
		{
			target_lvl = BLOCK_SIZE(i);

			if(act_size <= target_lvl)
				{
					break;
				}
		}
		/* if block exists */
		if(size > 0)
		{
			struct BlockMetaData* element = LIST_FIRST(block_ptr);
			LIST_REMOVE(block_ptr, element);
			element->is_free = 0;
			element->level = target_lvl;

			return (void*)(element + 1);
		}
		/* if no block exists
		 * point block_ptr to the list for the updated target_lvl and recalculate
		 * recalculate size = LIST_SIZE(block_ptr) before checking if (size > 0).
		 *
		 *
		 *
		 * */
		else
		{
			uint32 search_lvl = target_lvl + 1;
			uint32 half_size = BLOCK_SIZE(search_lvl) / 2;
			struct BlockMetaData* right_buddy;
			uint32 current_lvl = search_lvl - 1;
			while(search_lvl <= BUDDY_UPPER_LEVEL)
			{
				block_ptr = search_lvl;
				size = LIST_SIZE(block_ptr);
				if(size > 0)
				{
					//pick first block and split it
					struct BlockMetaData* element = LIST_FIRST(block_ptr);

					right_buddy = (void*)((uint8*)element + half_size);

					element->level = current_lvl;
					element->is_free = 1;
					right_buddy->level = current_lvl;
					right_buddy->is_free = 1;
					block_ptr = current_lvl;
					LIST_INSERT_HEAD(block_ptr, element);
					LIST_INSERT_AFTER(block_ptr, element, right_buddy);

				}
			}
		}

}

}

//===================================================
// [3] FREE BLOCK WITH COALESCING:
//===================================================
void free_block(void *va)
{
	//TODO: [PROJECT'26.GM#1] DYNAMIC ALLOCATOR - [3] free_block
	//Your code is here
	//Comment the following line
	panic("free_block() not implemented");
}

//=================================================================================//
//============================== BONUS FUNCTION ===================================//
//=================================================================================//

//===========================
// [1] REALLOCATE BLOCK:
//===========================
void *realloc_block(void* va, uint32 newSize)
{
	//TODO: [PROJECT'26.BONUS#1] KERNEL REALLOC - realloc_block
	//Your code is here
	//Comment the following line
	panic("realloc_block() Not implemented yet");
}
