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
typedef  size_t UINT ;
struct TYPE_3__ {size_t handles_size; scalar_t__* handles; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  scalar_t__ HGDIOBJ ;
typedef  TYPE_1__ EMFDRV_PDEVICE ;

/* Variables and functions */
 TYPE_1__* get_emf_physdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT EMFDRV_FindObject( PHYSDEV dev, HGDIOBJ obj )
{
    EMFDRV_PDEVICE *physDev = get_emf_physdev( dev );
    UINT index;

    for(index = 0; index < physDev->handles_size; index++)
        if(physDev->handles[index] == obj) break;

    if(index == physDev->handles_size) return 0;

    return index + 1;
}