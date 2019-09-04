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
struct TYPE_3__ {scalar_t__ MediaHandle; } ;
typedef  TYPE_1__* PEXT2_FILESYS ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NtClose (scalar_t__) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
Ext2CloseDevice( PEXT2_FILESYS Ext2Sys)
{
    NTSTATUS Status = STATUS_SUCCESS;

    if(Ext2Sys->MediaHandle)
    {
        Status = NtClose(Ext2Sys->MediaHandle);
    }

    return Status;
}