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
struct TYPE_3__ {scalar_t__ Ptr; scalar_t__ Root; scalar_t__ Size; } ;
typedef  TYPE_1__* PSAFE_READ ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */

BYTE ReadByte(PSAFE_READ pRead)
{
    if (pRead->Ptr + sizeof(BYTE) <= (pRead->Root + pRead->Size))
    {
        BYTE Value = *(PBYTE)pRead->Ptr;
        pRead->Ptr += sizeof(BYTE);
        return Value;
    }
    pRead->Ptr = pRead->Root + pRead->Size;
    return 0;
}