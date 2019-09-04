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
typedef  scalar_t__ ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disasm (scalar_t__*,scalar_t__*) ; 
 scalar_t__ GetLinearAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RepaintSource () ; 
 scalar_t__* tempCmd ; 
 int /*<<< orphan*/  ulOldDisasmOffset ; 
 int /*<<< orphan*/  usOldDisasmSegment ; 

void UnassembleOnePageDown(ULONG page)
{
    ULONG addr,addrorg,i;

    DPRINT((0,"UnassembleOnePageDown()\n"));

    addrorg = addr = GetLinearAddress(usOldDisasmSegment,ulOldDisasmOffset);

    DPRINT((0,"UnassembleOnePageDown(): addr = %.8X\n",addr));

    tempCmd[0]=0;
    for(i=0;i<page;i++)
	    Disasm(&addr,tempCmd);

    DPRINT((0,"UnassembleOnePageDown(): addr after = %.8X\n",addr));

    ulOldDisasmOffset += (addr - addrorg);
    RepaintSource();
}