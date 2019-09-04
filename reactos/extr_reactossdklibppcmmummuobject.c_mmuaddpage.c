#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int pteh; int ptel; } ;
struct TYPE_12__ {int proc; int addr; TYPE_1__ pte; } ;
typedef  TYPE_2__ ppc_map_t ;
struct TYPE_13__ {int phys; int addr; int proc; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ ppc_map_info_t ;
struct TYPE_15__ {TYPE_4__** tree; } ;
struct TYPE_14__ {TYPE_2__** leaves; } ;
typedef  TYPE_4__ MmuVsidTree ;
typedef  TYPE_5__ MmuVsidInfo ;

/* Variables and functions */
 int PPC_PAGE_ADDR (int) ; 
 int PPC_PAGE_MASK ; 
 size_t PPC_PAGE_NUMBER (int) ; 
 TYPE_2__* PpcPageTable ; 
 TYPE_2__* allocpage () ; 
 TYPE_4__* allocvsidtree () ; 
 TYPE_5__* findvsid (int) ; 
 int /*<<< orphan*/  fmtout (char*,...) ; 

int mmuaddpage(ppc_map_info_t *info, int count)
{
    int i, iva = 0, vsid, phys, virt;
    int ptehi;
    int ptelo, vsid_table_hi, vsid_table_lo;
    ppc_map_t *PagePtr;
    MmuVsidInfo *VsidInfo;
    MmuVsidTree *VsidTree;

    for(i = 0; i < count; i++)
    {
        info[i].phys &= ~PPC_PAGE_MASK;
        info[i].addr &= ~PPC_PAGE_MASK;

	virt = info[i].addr;
	vsid = ((info[i].addr >> 28) & 15) | (info[i].proc << 4);
	VsidInfo = findvsid(vsid);

	if(!VsidInfo) return -1;

	ptehi = (1 << 31) | (vsid << 7) | ((virt >> 22) & 0x3f);
	
	if(info[i].phys) {
	    PagePtr = &PpcPageTable[PPC_PAGE_NUMBER(info[i].phys)];
	} else {
	    PagePtr = allocpage();
	    if(!PagePtr)
	    {
		return 0;
	    }
	}

	phys = PPC_PAGE_ADDR((PagePtr - PpcPageTable));
	ptelo = phys & ~PPC_PAGE_MASK;
	
        if (phys < 0x30000)
        {
            /* Should not be allocating physical */
            fmtout("Allocated physical: %x, logical %x\n", phys, virt);
            fmtout("PagePtr %x (page %d)\n", PagePtr, i);
            fmtout("info [ %x %x %x %x ]\n", info[i].proc, info[i].addr, info[i].flags, info[i].phys);
            while(1);
        }

	/* Update page data */
	PagePtr->pte.pteh = ptehi;
	PagePtr->pte.ptel = ptelo;
	PagePtr->proc = info[i].proc;
	PagePtr->addr = virt;

	vsid_table_hi = virt >> 20 & 255;
	vsid_table_lo = virt >> 12 & 255;

	if(!VsidInfo->tree[vsid_table_hi])
	    VsidInfo->tree[vsid_table_hi] = allocvsidtree();
	VsidTree = VsidInfo->tree[vsid_table_hi];
	if(!VsidTree) return 0;
	VsidTree->leaves[vsid_table_lo] = PagePtr;

	__asm__("tlbie %0\n\tsync\n\tisync" : : "r" (iva));
    }
    return 1;
}