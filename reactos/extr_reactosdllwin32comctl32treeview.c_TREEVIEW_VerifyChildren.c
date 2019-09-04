#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* nextSibling; struct TYPE_4__* firstChild; } ;
typedef  TYPE_1__ TREEVIEW_ITEM ;
typedef  int /*<<< orphan*/  TREEVIEW_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  TREEVIEW_VerifyItem (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
TREEVIEW_VerifyChildren(TREEVIEW_INFO *infoPtr, const TREEVIEW_ITEM *item)
{
    const TREEVIEW_ITEM *child;
    assert(item != NULL);

    for (child = item->firstChild; child != NULL; child = child->nextSibling)
	TREEVIEW_VerifyItem(infoPtr, child);
}