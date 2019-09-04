#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
struct TYPE_9__ {int /*<<< orphan*/  bNtfUnicode; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pszText; scalar_t__ cchTextMax; int /*<<< orphan*/  lParam; int /*<<< orphan*/  cChildren; int /*<<< orphan*/  iSelectedImage; int /*<<< orphan*/  iImage; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {int mask; int /*<<< orphan*/ * pszText; scalar_t__ cchTextMax; int /*<<< orphan*/  lParam; int /*<<< orphan*/  cChildren; int /*<<< orphan*/  iSelectedImage; int /*<<< orphan*/  iImage; scalar_t__ stateMask; int /*<<< orphan*/  state; TYPE_2__* hItem; } ;
typedef  TYPE_1__ TVITEMW ;
typedef  TYPE_2__ TREEVIEW_ITEM ;
typedef  TYPE_3__ TREEVIEW_INFO ;
typedef  int /*<<< orphan*/ * LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int TVIF_TEXT ; 
 scalar_t__ WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_alloc (scalar_t__) ; 

__attribute__((used)) static VOID
TREEVIEW_TVItemFromItem(const TREEVIEW_INFO *infoPtr, UINT mask, TVITEMW *tvItem, TREEVIEW_ITEM *item)
{
    tvItem->mask = mask;
    tvItem->hItem = item;
    tvItem->state = item->state;
    tvItem->stateMask = 0;
    tvItem->iImage = item->iImage;
    tvItem->iSelectedImage = item->iSelectedImage;
    tvItem->cChildren = item->cChildren;
    tvItem->lParam = item->lParam;

    if(mask & TVIF_TEXT)
    {
        if (!infoPtr->bNtfUnicode)
        {
            tvItem->cchTextMax = WideCharToMultiByte( CP_ACP, 0, item->pszText, -1, NULL, 0, NULL, NULL );
            tvItem->pszText = heap_alloc (tvItem->cchTextMax);
            WideCharToMultiByte( CP_ACP, 0, item->pszText, -1, (LPSTR)tvItem->pszText, tvItem->cchTextMax, 0, 0 );
	}
        else
        {
            tvItem->cchTextMax = item->cchTextMax;
            tvItem->pszText = item->pszText;
        }
    }
    else
    {
        tvItem->cchTextMax = 0;
        tvItem->pszText = NULL;
    }
}