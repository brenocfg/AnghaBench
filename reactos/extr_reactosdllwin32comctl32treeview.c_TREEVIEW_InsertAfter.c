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
struct TYPE_5__ {struct TYPE_5__* firstChild; struct TYPE_5__* lastChild; struct TYPE_5__* prevSibling; struct TYPE_5__* nextSibling; struct TYPE_5__* parent; } ;
typedef  TYPE_1__ TREEVIEW_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
TREEVIEW_InsertAfter(TREEVIEW_ITEM *newItem, TREEVIEW_ITEM *sibling,
		     TREEVIEW_ITEM *parent)
{
    assert(parent != NULL);

    if (sibling != NULL)
    {
	assert(sibling->parent == parent);

	if (sibling->nextSibling != NULL)
	    sibling->nextSibling->prevSibling = newItem;

	newItem->nextSibling = sibling->nextSibling;
	sibling->nextSibling = newItem;
    }
    else
       newItem->nextSibling = NULL;

    newItem->prevSibling = sibling;

    if (parent->lastChild == sibling)
	parent->lastChild = newItem;

    if (parent->firstChild == NULL)
	parent->firstChild = newItem;
}