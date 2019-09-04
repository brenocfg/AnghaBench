#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_2__ {size_t handles_size; int /*<<< orphan*/  cur_handles; scalar_t__* handles; } ;
typedef  scalar_t__ PHYSDEV ;
typedef  TYPE_1__ METAFILEDRV_PDEVICE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOL MFDRV_RemoveHandle( PHYSDEV dev, UINT index )
{
    METAFILEDRV_PDEVICE *physDev = (METAFILEDRV_PDEVICE *)dev;
    BOOL ret = FALSE;

    if (index < physDev->handles_size && physDev->handles[index])
    {
        physDev->handles[index] = 0;
        physDev->cur_handles--;
        ret = TRUE;
    }
    return ret;
}