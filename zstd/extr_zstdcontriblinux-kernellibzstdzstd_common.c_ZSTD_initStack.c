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
struct TYPE_5__ {char* end; void* ptr; } ;
typedef  TYPE_1__ ZSTD_stack ;
struct TYPE_6__ {void* member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ ZSTD_customMem ;

/* Variables and functions */
 void* ZSTD_PTR_ALIGN (void*) ; 
 int /*<<< orphan*/ * ZSTD_stackAlloc ; 
 int /*<<< orphan*/ * ZSTD_stackFree ; 
 int /*<<< orphan*/  stack_push (TYPE_1__*,int) ; 

ZSTD_customMem ZSTD_initStack(void *workspace, size_t workspaceSize)
{
	ZSTD_customMem stackMem = {ZSTD_stackAlloc, ZSTD_stackFree, workspace};
	ZSTD_stack *stack = (ZSTD_stack *)workspace;
	/* Verify preconditions */
	if (!workspace || workspaceSize < sizeof(ZSTD_stack) || workspace != ZSTD_PTR_ALIGN(workspace)) {
		ZSTD_customMem error = {NULL, NULL, NULL};
		return error;
	}
	/* Initialize the stack */
	stack->ptr = workspace;
	stack->end = (char *)workspace + workspaceSize;
	stack_push(stack, sizeof(ZSTD_stack));
	return stackMem;
}