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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ pSRRemoveRestorePoint (scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__) ; 

__attribute__((used)) static void remove_restore_point(DWORD seq_number)
{
    DWORD res;

    res = pSRRemoveRestorePoint(seq_number);
    if (res != ERROR_SUCCESS)
        trace("Failed to remove the restore point : %08x\n", res);
}