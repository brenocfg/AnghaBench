#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int /*<<< orphan*/  hBrowseTV; } ;
typedef  TYPE_1__* PMAIN_WND_INFO ;
typedef  int /*<<< orphan*/ * HTREEITEM ;

/* Variables and functions */
 int /*<<< orphan*/  FreeItemTag (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ NodeHasChild (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * TreeView_GetChild (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TreeView_GetNextSibling (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TreeView_GetParent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VOID
TraverseTreeView(PMAIN_WND_INFO pInfo,
                 HTREEITEM hItem)
{
    while (NodeHasChild(pInfo, hItem))
    {
        HTREEITEM hChildItem;

        FreeItemTag(pInfo, hItem);

        hChildItem = TreeView_GetChild(pInfo->hBrowseTV,
                                       hItem);

        TraverseTreeView(pInfo,
                         hChildItem);

        hItem = TreeView_GetNextSibling(pInfo->hBrowseTV,
                                        hItem);
    }

    if (hItem)
    {
        /* loop the child items and free the tags */
        while (TRUE)
        {
            HTREEITEM hOldItem;

            FreeItemTag(pInfo, hItem);
            hOldItem = hItem;
            hItem = TreeView_GetNextSibling(pInfo->hBrowseTV,
                                            hItem);
            if (hItem == NULL)
            {
                hItem = hOldItem;
                break;
            }
        }

        hItem = TreeView_GetParent(pInfo->hBrowseTV,
                                   hItem);
    }
}