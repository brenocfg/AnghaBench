#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int style; scalar_t__ nb_items; TYPE_1__* items; } ;
struct TYPE_4__ {scalar_t__ selected; } ;
typedef  scalar_t__ LRESULT ;
typedef  scalar_t__* LPINT ;
typedef  TYPE_1__ LB_ITEMDATA ;
typedef  TYPE_2__ LB_DESCR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int LBS_MULTIPLESEL ; 
 scalar_t__ LB_ERR ; 

__attribute__((used)) static LRESULT LISTBOX_GetSelItems( const LB_DESCR *descr, INT max, LPINT array )
{
    INT i, count;
    const LB_ITEMDATA *item = descr->items;

    if (!(descr->style & LBS_MULTIPLESEL)) return LB_ERR;
    for (i = count = 0; (i < descr->nb_items) && (count < max); i++, item++)
        if (item->selected) array[count++] = i;
    return count;
}