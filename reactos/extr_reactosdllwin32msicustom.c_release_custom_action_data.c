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
struct TYPE_6__ {TYPE_1__* package; struct TYPE_6__* target; struct TYPE_6__* source; struct TYPE_6__* action; scalar_t__ handle; int /*<<< orphan*/  entry; int /*<<< orphan*/  refs; } ;
typedef  TYPE_2__ msi_custom_action_info ;
struct TYPE_5__ {int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_custom_action_cs ; 
 int /*<<< orphan*/  msi_free (TYPE_2__*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_custom_action_data( msi_custom_action_info *info )
{
    EnterCriticalSection( &msi_custom_action_cs );

    if (!--info->refs)
    {
        list_remove( &info->entry );
        if (info->handle)
            CloseHandle( info->handle );
        msi_free( info->action );
        msi_free( info->source );
        msi_free( info->target );
        msiobj_release( &info->package->hdr );
        msi_free( info );
    }

    LeaveCriticalSection( &msi_custom_action_cs );
}