#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* addr; } ;
typedef  TYPE_1__ ppc_map_t ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ MmuFreePage ;

/* Variables and functions */
 TYPE_2__* FreeList ; 
 void* MMU_ADDR_RESERVED ; 
 int NextPage ; 
 int PPC_PAGE_NUMBER (int /*<<< orphan*/ ) ; 
 TYPE_1__* PpcPageTable ; 
 int /*<<< orphan*/  RamSize ; 
 int /*<<< orphan*/  fmtout (char*,...) ; 
 int /*<<< orphan*/  mmuisfreepage (int) ; 

ppc_map_t *allocpage()
{
    MmuFreePage *FreePage = 0;

    if (FreeList)
    {
        if ((void *)FreeList == (void *)PpcPageTable)
        {
            fmtout("Problem! FreeList: page 0 is free\n");
            while(1);
        }

	FreePage = FreeList;
	FreeList = FreeList->next;
        ((ppc_map_t*)FreePage)->addr = MMU_ADDR_RESERVED;
	return ((ppc_map_t*)FreePage);
    }
    else
    {
        while(!mmuisfreepage(NextPage) && NextPage < PPC_PAGE_NUMBER(RamSize))
        {
            NextPage++;
        }
        if (NextPage < PPC_PAGE_NUMBER(RamSize))
        {
            if (NextPage < 0x30)
            {
                fmtout("Problem! NextPage is low (%x)\n", NextPage);
                while(1);
            }
            
            PpcPageTable[NextPage].addr = MMU_ADDR_RESERVED;
            return &PpcPageTable[NextPage++];
        }
        else
        {
            return NULL;
        }
    }
}