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
typedef  scalar_t__ USHORT ;
typedef  size_t ULONG ;
struct TYPE_3__ {scalar_t__ vendorid; int /*<<< orphan*/ * vendor_name; } ;
typedef  int /*<<< orphan*/ * LPSTR ;

/* Variables and functions */
 size_t DIM (TYPE_1__*) ; 
 TYPE_1__* PCIVendorIDs ; 

LPSTR FindPCIVendorName(USHORT vendorid)
{
    ULONG i;

    for(i=0;i<DIM(PCIVendorIDs);i++)
    {
        if(vendorid == PCIVendorIDs[i].vendorid)
            return PCIVendorIDs[i].vendor_name;
    }

    return NULL;
}