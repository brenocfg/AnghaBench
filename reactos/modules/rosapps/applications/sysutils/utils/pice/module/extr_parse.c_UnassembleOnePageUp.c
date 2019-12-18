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
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int LONG ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disasm (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  FindFunctionByAddress (scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ GetLinearAddress (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RepaintSource () ; 
 scalar_t__* tempCmd ; 
 scalar_t__ ulOldDisasmOffset ; 
 int /*<<< orphan*/  usOldDisasmSegment ; 

void UnassembleOnePageUp(ULONG page)
{
    ULONG addr,addrorg,addrbefore,start,end,i,addrstart;
    LONG offset;
    LPSTR pSymbol;

    DPRINT((0,"UnassembleOnePageUp()\n"));

    for(i=0;i<page;i++)
    {
        addrorg = addr = GetLinearAddress(usOldDisasmSegment,ulOldDisasmOffset);

        DPRINT((0,"UnassembleOnePageUp(): addrorg = %.8X\n",addr));

        offset = 1;

        if((pSymbol = FindFunctionByAddress(addrorg-offset,&start,&end)) )
        {
            offset = addrorg - start;
            DPRINT((0,"UnassembleOnePageUp(): %s @ offset = %u\n",pSymbol,offset));
        }
        else
        {
            // max instruction length is 15 bytes
            offset = 15;
        }

        // start at current address less offset
        addr = addrorg - offset;
        addrstart = addrorg;
        do
        {
            DPRINT((0,"UnassembleOnePageUp(): offset = %u addrorg %x addr %x\n",offset,addrorg,addr));
            addrbefore = addr;
            // disassemble while not reaching current instruction
            tempCmd[0]=0;
	        Disasm(&addr,tempCmd);
            DPRINT((0,"%.8X: %s\n",addrbefore,tempCmd));
        }while((addr != addrorg) && (addrbefore < addrorg));

        if((addrorg - addrstart)<=0)
            ulOldDisasmOffset--;
        else
            ulOldDisasmOffset -= (addrorg - addrbefore);

    }

    DPRINT((0,"UnassembleOnePageUp(): new addr = %.4X:%.8X\n",usOldDisasmSegment,ulOldDisasmOffset));

    RepaintSource();
}