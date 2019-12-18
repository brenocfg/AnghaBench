#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t t_len; TYPE_1__* t_data; } ;
struct TYPE_5__ {size_t t_hoff; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GETSTRUCT (TYPE_2__*) ; 
 void* MemoryContextAllocZero (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 

void *
ts_create_struct_from_tuple(HeapTuple tuple, MemoryContext mctx, size_t alloc_size,
							size_t copy_size)
{
	void *struct_ptr = MemoryContextAllocZero(mctx, alloc_size);

	/* Make sure the function is not used when the tuple contains NULLs */
	Assert(copy_size == tuple->t_len - tuple->t_data->t_hoff);
	memcpy(struct_ptr, GETSTRUCT(tuple), copy_size);

	return struct_ptr;
}