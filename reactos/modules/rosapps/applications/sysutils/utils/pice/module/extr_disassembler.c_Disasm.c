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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int dwFlags; int /*<<< orphan*/  wSel; int /*<<< orphan*/  szDisasm; int /*<<< orphan*/ * bpTarget; } ;
typedef  TYPE_1__ TDisassembler ;
typedef  scalar_t__* PULONG ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentCS ; 
 int DIS_ADDRESS32 ; 
 int DIS_DATA32 ; 
 scalar_t__ Disassembler (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN Disasm(PULONG pOffset,PUCHAR pchDst)
{
    TDisassembler dis;

    dis.dwFlags  = DIS_DATA32 | DIS_ADDRESS32;
    dis.bpTarget = (UCHAR*)*pOffset;
    dis.szDisasm = pchDst;
    dis.wSel = CurrentCS;

    *pOffset += (ULONG)Disassembler( &dis);
    return TRUE;
}