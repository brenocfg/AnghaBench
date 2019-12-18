#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ force; } ;
struct TYPE_7__ {TYPE_1__ obj; } ;
typedef  TYPE_2__ vlc_va_t ;
struct decoders {scalar_t__ deviceID; scalar_t__ cmd; scalar_t__ driverBuild; int /*<<< orphan*/ ** decoder_list; } ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {scalar_t__ vendor; struct decoders* devices; } ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_3__*) ; 
 scalar_t__ BLAnyDriver ; 
 scalar_t__ BLBelowBuild ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 TYPE_3__* gpu_blacklist ; 

bool directx_va_canUseDecoder(vlc_va_t *va, UINT VendorId, UINT DeviceId, const GUID *pCodec, UINT driverBuild)
{
    if (va->obj.force)
        return true;

    for (size_t i=0; i<ARRAY_SIZE(gpu_blacklist); i++)
    {
        if (gpu_blacklist[i].vendor == VendorId)
        {
            const struct decoders *pDevice = gpu_blacklist[i].devices;
            while (pDevice->deviceID != 0)
            {
                if (pDevice->deviceID == DeviceId)
                {
                    const GUID **pGuid = pDevice->decoder_list;
                    while (*pGuid != NULL)
                    {
                        if (IsEqualGUID(pCodec, *pGuid))
                        {
                            if (pDevice->cmd == BLAnyDriver)
                                return false;
                            if (pDevice->cmd == BLBelowBuild && driverBuild < pDevice->driverBuild)
                                return false;
                            break;
                        }
                        pGuid++;
                    }
                    return true;
                }
                pDevice++;
            }
            break;
        }
    }

    return true;
}