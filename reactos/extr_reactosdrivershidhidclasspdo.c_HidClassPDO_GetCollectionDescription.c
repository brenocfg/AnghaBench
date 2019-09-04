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
typedef  size_t ULONG ;
struct TYPE_6__ {size_t CollectionNumber; } ;
struct TYPE_5__ {size_t CollectionDescLength; TYPE_2__* CollectionDesc; } ;
typedef  TYPE_1__* PHIDP_DEVICE_DESC ;
typedef  TYPE_2__* PHIDP_COLLECTION_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,size_t) ; 
 int /*<<< orphan*/  FALSE ; 

PHIDP_COLLECTION_DESC
HidClassPDO_GetCollectionDescription(
    PHIDP_DEVICE_DESC DeviceDescription,
    ULONG CollectionNumber)
{
    ULONG Index;

    for(Index = 0; Index < DeviceDescription->CollectionDescLength; Index++)
    {
        if (DeviceDescription->CollectionDesc[Index].CollectionNumber == CollectionNumber)
        {
            //
            // found collection
            //
            return &DeviceDescription->CollectionDesc[Index];
        }
    }

    //
    // failed to find collection
    //
    DPRINT1("[HIDCLASS] GetCollectionDescription CollectionNumber %x not found\n", CollectionNumber);
    ASSERT(FALSE);
    return NULL;
}