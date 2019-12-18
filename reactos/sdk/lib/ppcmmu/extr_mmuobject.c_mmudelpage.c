#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* block; } ;
typedef  TYPE_1__ ppc_pteg_t ;
struct TYPE_13__ {int ptel; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ ppc_pte_t ;
struct TYPE_14__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  proc; } ;
typedef  TYPE_3__ ppc_map_t ;
struct TYPE_15__ {int phys; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; int /*<<< orphan*/  proc; } ;
typedef  TYPE_4__ ppc_map_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_PAGE_DIRTY ; 
 int PPC_PAGE_ADDR (int) ; 
 scalar_t__ PageMatch (int,TYPE_2__) ; 
 TYPE_3__* PpcPageTable ; 
 TYPE_1__* PtegFromPage (TYPE_3__*,int) ; 
 int /*<<< orphan*/  freepage (TYPE_3__*) ; 
 TYPE_3__* mmuvirtmap (int /*<<< orphan*/ ) ; 

void mmudelpage(ppc_map_info_t *info, int count)
{
    int i, j, k, ipa;
    ppc_map_t *PagePtr;
    ppc_pteg_t *PageEntry;
    ppc_pte_t ZeroPte = { 0 };

    for(i = 0; i < count; i++)
    {
	if (info[i].phys)
	{
	    ipa = info[i].phys;
	    PagePtr = &PpcPageTable[ipa];
	    info[i].proc = PagePtr->proc;
	    info[i].addr = PagePtr->addr;
	}
	else
	{
	    PagePtr = mmuvirtmap(info[i].addr);
	    ipa = PPC_PAGE_ADDR(PagePtr - PpcPageTable);
	}

	for(j = 0; j < 2; j++)
	{
	    PageEntry = PtegFromPage(PagePtr, j);
	    for(k = 0; k < 8; k++)
	    {
		if(PageMatch(ipa, PageEntry->block[k]))
		{
		    if(PageEntry->block[k].ptel & 0x100)
			info[i].flags |= MMU_PAGE_DIRTY;
		    PageEntry->block[k] = ZeroPte;
		}
	    }
	}
	freepage(PagePtr);
	__asm__("tlbie %0\n\tsync\n\tisync" : : "r" (info[i].addr));
    }
}