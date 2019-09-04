#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  const TREEVIEW_ITEM ;
typedef  int /*<<< orphan*/  TREEVIEW_INFO ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int /*<<< orphan*/  const* TREEVIEW_GetNextListItem (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* TREEVIEW_GetPrevListItem (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TREEVIEW_ITEM *
TREEVIEW_GetListItem(const TREEVIEW_INFO *infoPtr, TREEVIEW_ITEM *item,
		     LONG count)
{
    TREEVIEW_ITEM *(*next_item)(const TREEVIEW_INFO *, const TREEVIEW_ITEM *);
    TREEVIEW_ITEM *previousItem;

    assert(item != NULL);

    if (count > 0)
    {
	next_item = TREEVIEW_GetNextListItem;
    }
    else if (count < 0)
    {
	count = -count;
	next_item = TREEVIEW_GetPrevListItem;
    }
    else
	return item;

    do
    {
	previousItem = item;
	item = next_item(infoPtr, item);

    } while (--count && item != NULL);


    return item ? item : previousItem;
}