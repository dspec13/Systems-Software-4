/*
	CSE 109: Spring 2018
	Dylan Spector
	drs320
	Header file for Allocator Object
	Program #4
*/

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include"Allocation.h"
#include<stdio.h>

struct Allocator_t
{
	void* memory;    // points to the chunk of memory that the Allocator_t is using.
	size_t capacity; // must be a multiple of 16
	struct Allocation_t** allocationList; // dynamically resizable
	size_t listSize;     // How many in the list
	size_t listCapacity; // How many can be in the list (spots)
};

void makeAllocator(struct Allocator_t* it, size_t capacity);
void freeAllocator(struct Allocator_t* it);
void* allocate(struct Allocator_t* it, size_t amt);
void deallocate(struct Allocator_t* it, void* ptr);
void* getBase(struct Allocator_t* it);
size_t getUsed(struct Allocator_t* it);
size_t getCapacity(struct Allocator_t* it);
void printAllocations(struct Allocator_t* it, FILE* fd);
struct Allocation_t* getAllocation(struct Allocator_t* it, size_t index);
size_t numAllocations(struct Allocator_t* it);
void* riskyAlloc(struct Allocator_t* it, size_t size);

#endif
