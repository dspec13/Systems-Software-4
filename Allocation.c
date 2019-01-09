/*
	CSE 109: Spring 2018
	Dylan Spector
	drs320
	C file for Allocation Object
	Program #4
*/

#include"Allocation.h"
#include<stdio.h>
#include<stdlib.h>

void makeAllocation(struct Allocation_t* it, size_t start, size_t size)
{
	it->start = start;
	it->size = size;
	return;
}

void freeAllocation(struct Allocation_t* it)
{
	free(it);
	return;
}

size_t getStart(struct Allocation_t* it)
{
	return it->start;
}

size_t getEnd(struct Allocation_t* it)
{
    return (getStart(it) + getSize(it));
}

size_t getSize(struct Allocation_t* it)
{
    return it->size;
}

int doesOverlap(struct Allocation_t* it, size_t start, size_t size)
{
	size_t inclusiveEnd = (start+size-1);

	if(inclusiveEnd == getStart(it) || (inclusiveEnd > getStart(it) && inclusiveEnd < getEnd(it)))
	{
		return 1; // overlaps from the left
	}
	else if(getEnd(it)-1 == start || (getEnd(it)-1 > start && getEnd(it)-1 < start+size))
	{
		return 1; // overlaps from the right
	}
	return 0; // does not overlap
}
