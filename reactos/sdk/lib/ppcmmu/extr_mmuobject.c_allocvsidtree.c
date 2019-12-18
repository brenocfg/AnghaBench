#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ppc_map_t ;
struct TYPE_2__ {struct TYPE_2__* next; } ;
typedef  int /*<<< orphan*/  MmuVsidTree ;

/* Variables and functions */
 TYPE_1__* FreeTree ; 
 int /*<<< orphan*/ * NextTreePage ; 
 scalar_t__ PPC_PAGE_ADDR (int /*<<< orphan*/ *) ; 
 int PpcPageTable ; 
 int TreeAlloc ; 
 int /*<<< orphan*/ * allocpage () ; 

MmuVsidTree *allocvsidtree()
{
    if(FreeTree)
    {
	MmuVsidTree *result = (MmuVsidTree*)FreeTree;
	FreeTree = FreeTree->next;
	return result;
    }
    else if(TreeAlloc >= 3 || !NextTreePage)
    {
	ppc_map_t *map = allocpage();
	NextTreePage = (MmuVsidTree*)PPC_PAGE_ADDR((map - PpcPageTable));
	TreeAlloc = 1;
	return NextTreePage;
    }
    else
    {
	return &NextTreePage[TreeAlloc++];
    }
}