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
struct TYPE_5__ {int top_item; int nb_items; int style; int item_height; int page_size; int column_width; TYPE_1__* items; } ;
struct TYPE_4__ {int height; } ;
typedef  TYPE_2__ LB_DESCR ;
typedef  int INT ;

/* Variables and functions */
 int LBS_MULTICOLUMN ; 
 int LBS_OWNERDRAWVARIABLE ; 

__attribute__((used)) static INT LISTBOX_GetItemFromPoint( const LB_DESCR *descr, INT x, INT y )
{
    INT index = descr->top_item;

    if (!descr->nb_items) return -1;  /* No items */
    if (descr->style & LBS_OWNERDRAWVARIABLE)
    {
        INT pos = 0;
        if (y >= 0)
        {
            while (index < descr->nb_items)
            {
                if ((pos += descr->items[index].height) > y) break;
                index++;
            }
        }
        else
        {
            while (index > 0)
            {
                index--;
                if ((pos -= descr->items[index].height) <= y) break;
            }
        }
    }
    else if (descr->style & LBS_MULTICOLUMN)
    {
        if (y >= descr->item_height * descr->page_size) return -1;
        if (y >= 0) index += y / descr->item_height;
        if (x >= 0) index += (x / descr->column_width) * descr->page_size;
        else index -= (((x + 1) / descr->column_width) - 1) * descr->page_size;
    }
    else
    {
        index += (y / descr->item_height);
    }
    if (index < 0) return 0;
    if (index >= descr->nb_items) return -1;
    return index;
}