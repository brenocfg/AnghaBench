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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int /*<<< orphan*/  hBrowseTV; } ;
struct TYPE_5__ {scalar_t__ lParam; int /*<<< orphan*/  mask; int /*<<< orphan*/  hItem; } ;
typedef  TYPE_1__ TV_ITEM ;
typedef  int /*<<< orphan*/  PTEST_ITEM ;
typedef  TYPE_2__* PMAIN_WND_INFO ;
typedef  int /*<<< orphan*/  HTREEITEM ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVIF_PARAM ; 
 int /*<<< orphan*/  TreeView_GetItem (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static VOID
FreeItemTag(PMAIN_WND_INFO pInfo,
            HTREEITEM hItem)
{
    TV_ITEM tvItem;

    tvItem.hItem = hItem;
    tvItem.mask = TVIF_PARAM;

    (void)TreeView_GetItem(pInfo->hBrowseTV, &tvItem);

    HeapFree(GetProcessHeap(),
             0,
             (PTEST_ITEM)tvItem.lParam);
}