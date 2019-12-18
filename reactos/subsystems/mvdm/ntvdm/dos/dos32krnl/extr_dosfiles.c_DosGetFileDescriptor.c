#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  FirstSft; } ;
struct TYPE_3__ {size_t NumDescriptors; int /*<<< orphan*/  Link; int /*<<< orphan*/ * FileDescriptors; } ;
typedef  TYPE_1__* PDOS_SFT ;
typedef  int /*<<< orphan*/ * PDOS_FILE_DESCRIPTOR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  size_t BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FAR_POINTER (int /*<<< orphan*/ ) ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 TYPE_2__* SysVars ; 

PDOS_FILE_DESCRIPTOR DosGetFileDescriptor(BYTE Id)
{
    DWORD CurrentSft = SysVars->FirstSft;

    while (LOWORD(CurrentSft) != 0xFFFF)
    {
        PDOS_SFT Sft = (PDOS_SFT)FAR_POINTER(CurrentSft);

        /* Return it if it's in this table */
        if (Id <= Sft->NumDescriptors) return &Sft->FileDescriptors[Id];

        /* Go to the next table */
        Id -= Sft->NumDescriptors;
        CurrentSft = Sft->Link;
    }

    /* Invalid ID */
    return NULL;
}