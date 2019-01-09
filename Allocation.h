/*
	CSE 109: Spring 2018
	Dylan Spector
	drs320
	Header file for Allocation object
	Program #4
*/

#ifndef ALLOCATION_H
#define ALLOCATION_H

#include<stdio.h>

struct Allocation_t
{
	size_t start;
	size_t size; // used space
};

void makeAllocation(struct Allocation_t* it, size_t start, size_t size);
void freeAllocation(struct Allocation_t* it);
size_t getStart(struct Allocation_t* it);
size_t getEnd(struct Allocation_t* it);
size_t getSize(struct Allocation_t* it);
int doesOverlap(struct Allocation_t* it, size_t start, size_t size);

#endif
