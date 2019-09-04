#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * obj; } ;
struct TYPE_5__ {int /*<<< orphan*/  remote; int /*<<< orphan*/  dwThreadId; TYPE_1__ u; } ;
typedef  TYPE_2__ msi_handle_info ;
typedef  int /*<<< orphan*/  MSIOBJECTHDR ;
typedef  int MSIHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSI_handle_cs ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int) ; 
 int alloc_handle_table_entry () ; 
 TYPE_2__* msihandletable ; 
 int /*<<< orphan*/  msiobj_addref (int /*<<< orphan*/ *) ; 

MSIHANDLE alloc_msihandle( MSIOBJECTHDR *obj )
{
    msi_handle_info *entry;
    MSIHANDLE ret;

    EnterCriticalSection( &MSI_handle_cs );

    ret = alloc_handle_table_entry();
    if (ret)
    {
        entry = &msihandletable[ ret - 1 ];
        msiobj_addref( obj );
        entry->u.obj = obj;
        entry->dwThreadId = GetCurrentThreadId();
        entry->remote = FALSE;
    }

    LeaveCriticalSection( &MSI_handle_cs );

    TRACE("%p -> %d\n", obj, ret );

    return ret;
}