#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hBrowseTV; } ;
struct TYPE_5__ {int cChildren; int /*<<< orphan*/  mask; int /*<<< orphan*/  hItem; } ;
typedef  TYPE_1__ TV_ITEM ;
typedef  TYPE_2__* PMAIN_WND_INFO ;
typedef  int /*<<< orphan*/  HTREEITEM ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TVIF_CHILDREN ; 
 int /*<<< orphan*/  TreeView_GetItem (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static BOOL
NodeHasChild(PMAIN_WND_INFO pInfo,
             HTREEITEM hItem)
{
    TV_ITEM tvItem;

    tvItem.hItem = hItem;
    tvItem.mask = TVIF_CHILDREN;

    (void)TreeView_GetItem(pInfo->hBrowseTV, &tvItem);

    return (tvItem.cChildren == 1);
}