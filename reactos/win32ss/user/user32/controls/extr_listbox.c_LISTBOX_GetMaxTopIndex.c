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
struct TYPE_5__ {int style; size_t height; int nb_items; size_t width; size_t column_width; int page_size; TYPE_1__* items; } ;
struct TYPE_4__ {scalar_t__ height; } ;
typedef  TYPE_2__ LB_DESCR ;
typedef  size_t INT ;

/* Variables and functions */
 int LBS_MULTICOLUMN ; 
 int LBS_OWNERDRAWVARIABLE ; 

__attribute__((used)) static INT LISTBOX_GetMaxTopIndex( const LB_DESCR *descr )
{
    INT max, page;

    if (descr->style & LBS_OWNERDRAWVARIABLE)
    {
        page = descr->height;
        for (max = descr->nb_items - 1; max >= 0; max--)
            if ((page -= descr->items[max].height) < 0) break;
        if (max < descr->nb_items - 1) max++;
    }
    else if (descr->style & LBS_MULTICOLUMN)
    {
        if ((page = descr->width / descr->column_width) < 1) page = 1;
        max = (descr->nb_items + descr->page_size - 1) / descr->page_size;
        max = (max - page) * descr->page_size;
    }
    else
    {
        max = descr->nb_items - descr->page_size;
    }
    if (max < 0) max = 0;
    return max;
}