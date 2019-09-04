#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vaddr_t ;
typedef  int /*<<< orphan*/  ppc_map_t ;
struct TYPE_5__ {TYPE_1__** tree; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** leaves; } ;
typedef  TYPE_1__ MmuVsidTree ;
typedef  TYPE_2__ MmuVsidInfo ;

/* Variables and functions */
 TYPE_2__** Segs ; 

ppc_map_t *mmuvirtmap(vaddr_t addr)
{
    int seg = (addr >> 28) & 15;
    MmuVsidInfo *seginfo = Segs[seg];
    MmuVsidTree *segtree = 0;
    if(!seginfo) return 0;
    segtree = seginfo->tree[(addr >> 20) & 255];
    if(!segtree) return 0;
    return segtree->leaves[(addr >> 12) & 255];
}