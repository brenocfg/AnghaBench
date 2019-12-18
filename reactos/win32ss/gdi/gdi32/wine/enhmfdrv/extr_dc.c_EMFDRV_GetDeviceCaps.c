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
struct TYPE_3__ {int /*<<< orphan*/  ref_dc; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_1__ EMFDRV_PDEVICE ;

/* Variables and functions */
 int /*<<< orphan*/  GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_emf_physdev (int /*<<< orphan*/ ) ; 

INT EMFDRV_GetDeviceCaps(PHYSDEV dev, INT cap)
{
    EMFDRV_PDEVICE *physDev = get_emf_physdev( dev );

    return GetDeviceCaps( physDev->ref_dc, cap );
}