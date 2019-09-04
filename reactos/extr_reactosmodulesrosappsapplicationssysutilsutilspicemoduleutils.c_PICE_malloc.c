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
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (void*) ; 
 void* ExAllocatePool (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  PagedPool ; 

void * PICE_malloc( size_t numBytes, BOOLEAN fromPaged )
{
	void* res = ExAllocatePool( (fromPaged)?PagedPool:NonPagedPool, numBytes );
	ASSERT(res);
	return res;
}