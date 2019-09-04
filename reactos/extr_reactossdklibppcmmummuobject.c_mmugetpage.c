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
typedef  int vaddr_t ;
struct TYPE_6__ {int proc; int addr; } ;
typedef  TYPE_1__ ppc_map_t ;
struct TYPE_7__ {int addr; int proc; size_t phys; void* flags; } ;
typedef  TYPE_2__ ppc_map_info_t ;

/* Variables and functions */
 void* MMU_ALL_RW ; 
 scalar_t__ PAGETAB ; 
 size_t PPC_PAGE_ADDR (TYPE_1__*) ; 
 int PpcPageTable ; 
 TYPE_1__* mmuvirtmap (int) ; 

void mmugetpage(ppc_map_info_t *info, int count)
{
    int i;
    ppc_map_t *PagePtr;
    
    for( i = 0; i < count; i++ )
    {
	if(!info[i].addr && !info[i].proc)
	{
	    PagePtr = &((ppc_map_t*)PAGETAB)[info[i].phys];
            info[i].proc = PagePtr->proc;
            info[i].addr = PagePtr->addr;
            info[i].flags = MMU_ALL_RW;
	} else {
	    vaddr_t addr = info[i].addr;
	    int vsid = ((addr >> 28) & 15) | (info[i].proc << 4);
	    PagePtr = mmuvirtmap(info[i].addr);
	    if(!PagePtr)
		info[i].phys = 0;
	    else
	    {
		info[i].phys = PPC_PAGE_ADDR(PagePtr - PpcPageTable);
		info[i].flags = MMU_ALL_RW; // HACK
	    }
	}
    }
}