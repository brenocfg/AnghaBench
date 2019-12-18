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
typedef  int /*<<< orphan*/  ppc_map_t ;
typedef  int /*<<< orphan*/  paddr_t ;
struct TYPE_3__ {scalar_t__* tree; } ;
typedef  TYPE_1__ MmuVsidInfo ;

/* Variables and functions */
 size_t PPC_PAGE_NUMBER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PpcPageTable ; 
 TYPE_1__* findvsid (int) ; 
 int /*<<< orphan*/  freepage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freevsidtree (scalar_t__) ; 

void freevsid(int vsid)
{
    int i;
    MmuVsidInfo *info = findvsid(vsid);
    if(!info) return;
    ppc_map_t *map = &PpcPageTable[PPC_PAGE_NUMBER((paddr_t)info)];
    for(i = 0; i < 256; i++)
    {
	if(info->tree[i]) 
	    freevsidtree(info->tree[i]);
    }
    freepage(map);
}