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
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONG ;
typedef  int UCHAR ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  Mem ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KdbpPrint (char*,scalar_t__) ; 
 int /*<<< orphan*/  KdbpSafeReadMemory (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
KdbpShouldStepOverInstruction(
    ULONG_PTR Eip)
{
    UCHAR Mem[3];
    ULONG i = 0;

    if (!NT_SUCCESS(KdbpSafeReadMemory(Mem, (PVOID)Eip, sizeof (Mem))))
    {
        KdbpPrint("Couldn't access memory at 0x%p\n", Eip);
        return FALSE;
    }

    /* Check if the current instruction is a call. */
    while ((i < sizeof (Mem)) && (Mem[i] == 0x66 || Mem[i] == 0x67))
        i++;

    if (i == sizeof (Mem))
        return FALSE;

    if (Mem[i] == 0xE8 || Mem[i] == 0x9A || Mem[i] == 0xF2 || Mem[i] == 0xF3 ||
        (((i + 1) < sizeof (Mem)) && Mem[i] == 0xFF && (Mem[i+1] & 0x38) == 0x10))
    {
        return TRUE;
    }

    return FALSE;
}