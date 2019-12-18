#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ptr; scalar_t__ end; } ;
typedef  TYPE_1__ ZSTD_stack ;
typedef  int /*<<< orphan*/  const BYTE ;

/* Variables and functions */
 scalar_t__ ZSTD_PTR_ALIGN (int /*<<< orphan*/ ) ; 
 void* stack_push (TYPE_1__*,size_t) ; 

void *ZSTD_stackAllocAll(void *opaque, size_t *size)
{
	ZSTD_stack *stack = (ZSTD_stack *)opaque;
	*size = (BYTE const *)stack->end - (BYTE *)ZSTD_PTR_ALIGN(stack->ptr);
	return stack_push(stack, *size);
}