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
struct TYPE_4__ {scalar_t__ ref; } ;
typedef  TYPE_1__ ref_counted_vtbl ;
typedef  int /*<<< orphan*/  IUnknownVtbl ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 TYPE_1__* current_vtbl ; 
 int /*<<< orphan*/  delegating_vtbl_section ; 

void release_delegating_vtbl(IUnknownVtbl *vtbl)
{
    ref_counted_vtbl *table = (ref_counted_vtbl*)((DWORD *)vtbl - 1);

    EnterCriticalSection(&delegating_vtbl_section);
    table->ref--;
    TRACE("ref now %d\n", table->ref);
    if(table->ref == 0 && table != current_vtbl)
    {
        TRACE("... and we're not current so free'ing\n");
        HeapFree(GetProcessHeap(), 0, table);
    }
    LeaveCriticalSection(&delegating_vtbl_section);
}