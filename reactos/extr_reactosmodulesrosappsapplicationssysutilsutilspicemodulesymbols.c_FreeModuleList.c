#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__* PDEBUG_MODULE ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  ExFreePool (TYPE_1__*) ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 

VOID FreeModuleList( PDEBUG_MODULE pm )
{
	PDEBUG_MODULE pNext = pm;

	ENTER_FUNC();

	while( pNext ){
		pNext = pm->next;
		ExFreePool( pm );
	}
	LEAVE_FUNC();
}