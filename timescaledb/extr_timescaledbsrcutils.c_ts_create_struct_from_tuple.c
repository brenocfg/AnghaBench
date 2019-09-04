#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 void* MemoryContextAllocZero (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 

void *
ts_create_struct_from_tuple(HeapTuple tuple, MemoryContext mctx, size_t alloc_size,
							size_t copy_size)
{
	void *struct_ptr = MemoryContextAllocZero(mctx, alloc_size);

	memcpy(struct_ptr, GETSTRUCT(tuple), copy_size);

	return struct_ptr;
}