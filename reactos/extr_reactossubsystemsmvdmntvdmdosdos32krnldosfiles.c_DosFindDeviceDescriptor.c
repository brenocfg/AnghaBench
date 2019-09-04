#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_6__ {scalar_t__ FirstSft; } ;
struct TYPE_5__ {size_t NumDescriptors; scalar_t__ Link; TYPE_1__* FileDescriptors; } ;
struct TYPE_4__ {scalar_t__ RefCount; int DeviceInfo; scalar_t__ DevicePointer; } ;
typedef  TYPE_2__* PDOS_SFT ;
typedef  scalar_t__ DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FAR_POINTER (scalar_t__) ; 
 int FILE_INFO_DEVICE ; 
 int LOWORD (scalar_t__) ; 
 TYPE_3__* SysVars ; 

BYTE DosFindDeviceDescriptor(DWORD DevicePointer)
{
    UINT i;
    BYTE Count = 0;
    DWORD CurrentSft = SysVars->FirstSft;

    while (LOWORD(CurrentSft) != 0xFFFF)
    {
        PDOS_SFT Sft = (PDOS_SFT)FAR_POINTER(CurrentSft);

        for (i = 0; i < Sft->NumDescriptors; i++)
        {
            if ((Sft->FileDescriptors[i].RefCount > 0)
                && (Sft->FileDescriptors[i].DeviceInfo & FILE_INFO_DEVICE)
                && (Sft->FileDescriptors[i].DevicePointer == DevicePointer))
            {
                return Count;
            }

            Count++;
        }

        /* Go to the next table */
        CurrentSft = Sft->Link;
    }

    /* Invalid ID */
    return 0xFF;
}