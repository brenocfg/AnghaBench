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
typedef  int /*<<< orphan*/  ZSTD_stack ;

/* Variables and functions */
 void* stack_push (int /*<<< orphan*/ *,size_t) ; 

void *ZSTD_stackAlloc(void *opaque, size_t size)
{
	ZSTD_stack *stack = (ZSTD_stack *)opaque;
	return stack_push(stack, size);
}