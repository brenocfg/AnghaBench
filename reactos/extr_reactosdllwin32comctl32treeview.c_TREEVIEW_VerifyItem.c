#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  items; } ;
struct TYPE_10__ {scalar_t__ iLevel; struct TYPE_10__ const* parent; } ;
typedef  TYPE_1__ TREEVIEW_ITEM ;
typedef  TYPE_2__ TREEVIEW_INFO ;

/* Variables and functions */
 int DPA_GetPtrIndex (int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/  TREEVIEW_VerifyChildren (TYPE_2__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  TREEVIEW_VerifyItemCommon (TYPE_2__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline void
TREEVIEW_VerifyItem(TREEVIEW_INFO *infoPtr, const TREEVIEW_ITEM *item)
{
    assert(item != NULL);

    assert(item->parent != NULL);
    assert(item->parent != item);
    assert(item->iLevel == item->parent->iLevel + 1);

    assert(DPA_GetPtrIndex(infoPtr->items, item) != -1);

    TREEVIEW_VerifyItemCommon(infoPtr, item);

    TREEVIEW_VerifyChildren(infoPtr, item);
}