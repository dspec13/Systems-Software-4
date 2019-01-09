/*
	CSE 109: Spring 2018
	Dylan Spector
	C file for Allocator Object
	Program #4
*/

#include"Allocator.h"
#include"Allocation.h"
#include<stdio.h>
#include<stdlib.h>

void makeAllocator(struct Allocator_t* it, size_t capacity)
{
	// Rounds capacity up to the closest multiple of 16
	if(capacity > 16)
	{
		capacity += 16 - (capacity % 16);
	}
	else if(capacity != 0)
	{
		capacity = 16;
	}
	capacity -= 16;

	it->memory = (void*)malloc(capacity);
	it->capacity = capacity;
	it->allocationList = NULL;
	it->listSize = 0;
	it->listCapacity = 0;
}

void freeAllocator(struct Allocator_t* it)
{
	free(it->memory);
	for(size_t i = 0; i < numAllocations(it); i++)
	{
		free(it->allocationList[i]);
	}
	free(it);
	return;
}

void* allocate(struct Allocator_t* it, size_t amt)
{
	// If allocationList is full, expand it.
	if(it->listSize == it->listCapacity)
	{
		// Create a newList with an expanded capacity
		size_t newCapacity = (it->listCapacity)*2 + 1;
		struct Allocation_t** expandedAllocationList = (struct Allocation_t**)malloc(newCapacity * sizeof(struct Allocation_t*));
		for(size_t i = 0; i < it->listCapacity; i++)
		{
			expandedAllocationList[i] = it->allocationList[i];
		}

   		for(size_t i = 0; i < numAllocations(it); i++)
   	 	{
    	    free(it->allocationList[i]);
	    }
		free(it->allocationList);

		it->allocationList = expandedAllocationList;
		it->listCapacity = newCapacity;
	}

	// Find starting location of allocation.
	if(amt > 16)
	{
		amt += 16 - (amt % 16);
	}
	else if(amt != 0)
	{
		amt = 16;
	}

	if(amt > it->capacity)
	{
		return NULL;
	}

	int	overlapFound = 0;
	int assignedStart = -1;
	for(size_t start = 0; start <= getCapacity(it)-16; start+=16)
	{
		for(size_t i = 0; i < it->listSize; i++)
		{
			if(!doesOverlap(getAllocation(it, i), start, amt))
			{
				continue;
			}
			else
			{
				overlapFound = 1;
				break;
			}
		}
		if(overlapFound)
		{
			overlapFound = 0;
		}
		else
		{
			assignedStart = start;
			break;
		}
	}

	// If space no was found, add Allocation_t to List
	if(assignedStart == -1)
	{
		return NULL;
	}
	else
	{
		struct Allocation_t* newAllocation = (struct Allocation_t*)malloc(1* sizeof(struct Allocation_t)); 
		makeAllocation(newAllocation, assignedStart, amt);
		it->allocationList[numAllocations(it)] = newAllocation;
		(it->listSize)++;
		return getBase(it) + assignedStart;
	}
}


void deallocate(struct Allocator_t* it, void* ptr)
{
	if(ptr == NULL)
	{
		return;
	}

	for(size_t i = 0; i < it->listSize; i++)
	{
		struct Allocation_t* current = getAllocation(it, i);
		if(ptr == getBase(it) + getStart(current))
		{
			freeAllocation(current);
			for(size_t j = i; j < (it->listSize) - 1; j++)
			{
				it->allocationList[j] = it->allocationList[j+1];
			}
			(it->listSize)--;
			return;
		}
	}

	// If ptr was not found, throw an error
	fprintf(stderr, "Corruption in Free");
	exit(1);
}

void* getBase(struct Allocator_t* it)
{
	return it->memory;
}

size_t getUsed(struct Allocator_t* it)
{
	size_t sum = 0;
	for(size_t i = 0; i < it->listSize; i++)
	{
		sum += getSize(getAllocation(it, i));
	}
	return sum;
}

size_t getCapacity(struct Allocator_t* it)
{
	return it->capacity;
}

struct Allocation_t* getAllocation(struct Allocator_t* it, size_t index)
{
	if(index >= 0 && index < numAllocations(it))
	{
		return it->allocationList[index];
	}
	return NULL;
}

size_t numAllocations(struct Allocator_t* it)
{
	return it->listSize;
}

void* riskyAlloc(struct Allocator_t* it, size_t size)
{
	if(size <= it->capacity - getUsed(it))
	{
		return allocate(it, size);
	}
	else if(getBase(it) == realloc(getBase(it), it->capacity*2))
	{
		return allocate(it, size);
	}
	return NULL;
}
