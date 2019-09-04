#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * unk; } ;
struct TYPE_4__ {TYPE_1__ u; int /*<<< orphan*/  remote; } ;
typedef  size_t MSIHANDLE ;
typedef  int /*<<< orphan*/  IUnknown ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSI_handle_cs ; 
 TYPE_2__* msihandletable ; 
 size_t msihandletable_size ; 

IUnknown *msi_get_remote( MSIHANDLE handle )
{
    IUnknown *unk = NULL;

    EnterCriticalSection( &MSI_handle_cs );
    handle--;
    if( handle>=msihandletable_size )
        goto out;
    if( !msihandletable[handle].remote)
        goto out;
    unk = msihandletable[handle].u.unk;
    if( unk )
        IUnknown_AddRef( unk );

out:
    LeaveCriticalSection( &MSI_handle_cs );

    return unk;
}