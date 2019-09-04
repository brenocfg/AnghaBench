#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pStorage; } ;
struct TYPE_9__ {TYPE_2__* root; int /*<<< orphan*/  hwndList; } ;
struct TYPE_11__ {TYPE_1__ search; TYPE_4__* pCHMInfo; } ;
struct TYPE_10__ {int /*<<< orphan*/  next; } ;
typedef  TYPE_2__ SearchItem ;
typedef  TYPE_3__ HHInfo ;
typedef  TYPE_4__ CHMInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ReleaseSearch (TYPE_3__*) ; 
 int /*<<< orphan*/  SearchCHM_Storage (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* alloc_search_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_search_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void InitSearch(HHInfo *info, const char *needle)
{
    CHMInfo *chm = info->pCHMInfo;
    SearchItem *root_item = alloc_search_item(NULL, NULL);

    SearchCHM_Storage(root_item, chm->pStorage, needle);
    fill_search_tree(info->search.hwndList, root_item->next);
    if(info->search.root)
        ReleaseSearch(info);
    info->search.root = root_item;
}