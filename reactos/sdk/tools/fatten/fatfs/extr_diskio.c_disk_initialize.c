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
typedef  int /*<<< orphan*/  DSTATUS ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  STA_NOINIT ; 

DSTATUS disk_initialize(
    BYTE pdrv        /* Physical drive nmuber (0..) */
    )
{
    if (pdrv == 0) /* only one drive (image file) supported atm. */
    {
        return 0;
    }
    return STA_NOINIT;
}