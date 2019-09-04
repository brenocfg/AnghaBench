#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ root; } ;
struct TYPE_8__ {int state; scalar_t__ parent; int /*<<< orphan*/ * lastChild; struct TYPE_8__* prevSibling; } ;
typedef  TYPE_1__ TREEVIEW_ITEM ;
typedef  TYPE_2__ TREEVIEW_INFO ;

/* Variables and functions */
 TYPE_1__* TREEVIEW_GetLastListItem (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int TVIS_EXPANDED ; 

__attribute__((used)) static TREEVIEW_ITEM *
TREEVIEW_GetPrevListItem(const TREEVIEW_INFO *infoPtr, const TREEVIEW_ITEM *tvItem)
{
    if (tvItem->prevSibling)
    {
	/* This item has a prevSibling, get the last item in the sibling's tree. */
	TREEVIEW_ITEM *upItem = tvItem->prevSibling;

	if ((upItem->state & TVIS_EXPANDED) && upItem->lastChild != NULL)
	    return TREEVIEW_GetLastListItem(infoPtr, upItem->lastChild);
	else
	    return upItem;
    }
    else
    {
	/* this item does not have a prevSibling, get the parent */
	return (tvItem->parent != infoPtr->root) ? tvItem->parent : NULL;
    }
}