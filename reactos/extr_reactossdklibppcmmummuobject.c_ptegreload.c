#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vaddr_t ;
typedef  int /*<<< orphan*/  ppc_trap_frame_t ;
struct TYPE_5__ {int pteh; } ;
struct TYPE_6__ {TYPE_1__ pte; } ;
typedef  TYPE_2__ ppc_map_t ;
struct TYPE_7__ {TYPE_1__* block; } ;

/* Variables and functions */
 int Clock ; 
 TYPE_4__* PpcHashedPTE ; 
 int PtegNumber (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* mmuvirtmap (int /*<<< orphan*/ ) ; 

int ptegreload(ppc_trap_frame_t *frame, vaddr_t addr)
{
    int hfun = (Clock >> 3) & 1, ptegnum = PtegNumber(addr, hfun);
    ppc_map_t *map = mmuvirtmap(addr);
    if(!map) return 0;
    map->pte.pteh = (map->pte.pteh & ~64) | (hfun << 6);
    PpcHashedPTE[ptegnum].block[Clock & 7] = map->pte;
#if 0
    fmtout("Reloading addr %x (phys %x) at %x[%x] (%x:%x)\r\n",
	   addr, PPC_PAGE_ADDR(map - PpcPageTable), ptegnum, Clock & 15,
	   PpcHashedPTE[ptegnum].block[Clock&7].pteh,
	   PpcHashedPTE[ptegnum].block[Clock&7].ptel);
#endif
    Clock++;
    __asm__("tlbie %0\n\tsync\n\tisync" : : "r" (addr));
    return 1;
}