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
struct TYPE_3__ {scalar_t__ MasterBootRecordMagic; } ;
typedef  TYPE_1__* PMASTER_BOOT_RECORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ BOOT_RECORD_SIGNATURE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOL CheckAgainstMBR(PMASTER_BOOT_RECORD Sector)
{
    if (Sector->MasterBootRecordMagic != BOOT_RECORD_SIGNATURE)
    {
        return FALSE;
    }

    return TRUE;
}