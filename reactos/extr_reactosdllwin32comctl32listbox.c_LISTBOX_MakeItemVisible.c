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
struct TYPE_6__ {scalar_t__ top_item; int style; scalar_t__ width; int column_width; scalar_t__ page_size; int height; int item_height; TYPE_1__* items; } ;
struct TYPE_5__ {int height; } ;
typedef  TYPE_2__ LB_DESCR ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int LBS_MULTICOLUMN ; 
 int LBS_OWNERDRAWVARIABLE ; 
 int /*<<< orphan*/  LISTBOX_SetTopItem (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void LISTBOX_MakeItemVisible( LB_DESCR *descr, INT index, BOOL fully )
{
    INT top;

    TRACE("current top item %d, index %d, fully %d\n", descr->top_item, index, fully);

    if (index <= descr->top_item) top = index;
    else if (descr->style & LBS_MULTICOLUMN)
    {
        INT cols = descr->width;
        if (!fully) cols += descr->column_width - 1;
        if (cols >= descr->column_width) cols /= descr->column_width;
        else cols = 1;
        if (index < descr->top_item + (descr->page_size * cols)) return;
        top = index - descr->page_size * (cols - 1);
    }
    else if (descr->style & LBS_OWNERDRAWVARIABLE)
    {
        INT height = fully ? descr->items[index].height : 1;
        for (top = index; top > descr->top_item; top--)
            if ((height += descr->items[top-1].height) > descr->height) break;
    }
    else
    {
        if (index < descr->top_item + descr->page_size) return;
        if (!fully && (index == descr->top_item + descr->page_size) &&
            (descr->height > (descr->page_size * descr->item_height))) return;
        top = index - descr->page_size + 1;
    }
    LISTBOX_SetTopItem( descr, top, TRUE );
}