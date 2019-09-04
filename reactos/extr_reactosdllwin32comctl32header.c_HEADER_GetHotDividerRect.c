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
struct TYPE_12__ {size_t iHotDivider; scalar_t__ uNumItem; int /*<<< orphan*/  hwndSelf; TYPE_3__* items; } ;
struct TYPE_9__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; scalar_t__ right; scalar_t__ left; } ;
struct TYPE_11__ {TYPE_1__ rect; } ;
struct TYPE_10__ {scalar_t__ left; scalar_t__ right; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; } ;
typedef  TYPE_2__ RECT ;
typedef  size_t INT ;
typedef  TYPE_3__ HEADER_ITEM ;
typedef  TYPE_4__ HEADER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 size_t HEADER_OrderToIndex (TYPE_4__ const*,size_t) ; 
 int HOT_DIVIDER_WIDTH ; 

__attribute__((used)) static void HEADER_GetHotDividerRect(const HEADER_INFO *infoPtr, RECT *r)
{
    INT iDivider = infoPtr->iHotDivider;
    if (infoPtr->uNumItem > 0)
    {
        HEADER_ITEM *lpItem;
        
        if (iDivider < infoPtr->uNumItem)
        {
            lpItem = &infoPtr->items[iDivider];
            r->left  = lpItem->rect.left - HOT_DIVIDER_WIDTH/2;
            r->right = lpItem->rect.left + HOT_DIVIDER_WIDTH/2;
        }
        else
        {
            lpItem = &infoPtr->items[HEADER_OrderToIndex(infoPtr, infoPtr->uNumItem-1)];
            r->left  = lpItem->rect.right - HOT_DIVIDER_WIDTH/2;
            r->right = lpItem->rect.right + HOT_DIVIDER_WIDTH/2;
        }
        r->top    = lpItem->rect.top;
        r->bottom = lpItem->rect.bottom;
    }
    else
    {
        RECT clientRect;
        GetClientRect(infoPtr->hwndSelf, &clientRect);
        *r = clientRect;
        r->right = r->left + HOT_DIVIDER_WIDTH/2;
    }
}