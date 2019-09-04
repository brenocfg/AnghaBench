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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {scalar_t__ Peb; } ;
typedef  scalar_t__ PPEB ;
typedef  TYPE_1__* PEPROCESS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* IoGetCurrentProcess () ; 
 int /*<<< orphan*/  IsAddressValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  ListDriverModules () ; 
 int /*<<< orphan*/  ListUserModules (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pdebug_module_head ; 
 int /*<<< orphan*/  pdebug_module_tail ; 

BOOLEAN BuildModuleList( void )
{
 	PPEB peb;
	PEPROCESS tsk;
	ENTER_FUNC();

	pdebug_module_tail = pdebug_module_head;
	tsk = IoGetCurrentProcess();
	ASSERT(IsAddressValid((ULONG)tsk));
	if( tsk  ){
		peb = tsk->Peb;
		if( peb ){
			if( !ListUserModules( peb ) ){
				LEAVE_FUNC();
				return FALSE;
			}
		}
	}
	if( !ListDriverModules() ){
		LEAVE_FUNC();
		return FALSE;
	}
	LEAVE_FUNC();
	return TRUE;
}