#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ppc_map_t ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ MmuVsidInfo ;

/* Variables and functions */
 TYPE_1__* VsidHead ; 
 int /*<<< orphan*/  dumpvsid (TYPE_1__*) ; 
 int /*<<< orphan*/  fmtout (char*) ; 

void dumpmap()
{
    int i,j;
    ppc_map_t *map;
    MmuVsidInfo *vsid;
    fmtout("Address spaces:\n");
    for (vsid = VsidHead; vsid; vsid = vsid->next)
    {
        dumpvsid(vsid);
    }
}