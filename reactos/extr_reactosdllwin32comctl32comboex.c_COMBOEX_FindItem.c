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
struct TYPE_6__ {struct TYPE_6__* next; } ;
struct TYPE_5__ {scalar_t__ nb_items; TYPE_2__* items; TYPE_2__ edit; } ;
typedef  scalar_t__ INT_PTR ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ COMBOEX_INFO ;
typedef  TYPE_2__ CBE_ITEMDATA ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 

__attribute__((used)) static CBE_ITEMDATA *COMBOEX_FindItem(COMBOEX_INFO *infoPtr, INT_PTR index)
{
    CBE_ITEMDATA *item;
    INT i;

    if ((index >= infoPtr->nb_items) || (index < -1))
	return NULL;
    if (index == -1)
	return &infoPtr->edit;
    item = infoPtr->items;
    i = infoPtr->nb_items - 1;

    /* find the item in the list */
    while (item && (i > index)) {
	item = item->next;
	i--;
    }
    if (!item || (i != index)) {
	ERR("COMBOBOXEX item structures broken. Please report!\n");
	return 0;
    }
    return item;
}