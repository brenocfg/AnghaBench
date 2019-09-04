#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t nb_items; scalar_t__ width; scalar_t__ height; int style; size_t page_size; size_t top_item; size_t column_width; size_t item_height; scalar_t__ horz_pos; TYPE_1__* items; } ;
struct TYPE_10__ {scalar_t__ left; scalar_t__ right; scalar_t__ top; scalar_t__ bottom; } ;
struct TYPE_9__ {scalar_t__ height; } ;
typedef  TYPE_2__ RECT ;
typedef  int LRESULT ;
typedef  TYPE_3__ LB_DESCR ;
typedef  size_t INT ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_INDEX ; 
 int LBS_MULTICOLUMN ; 
 int LBS_OWNERDRAWVARIABLE ; 
 int LB_ERR ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SetRectEmpty (TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_2__*) ; 

__attribute__((used)) static LRESULT LISTBOX_GetItemRect( const LB_DESCR *descr, INT index, RECT *rect )
{
    /* Index <= 0 is legal even on empty listboxes */
    if (index && (index >= descr->nb_items))
    {
        SetRectEmpty(rect);
        SetLastError(ERROR_INVALID_INDEX);
        return LB_ERR;
    }
    SetRect( rect, 0, 0, descr->width, descr->height );
    if (descr->style & LBS_MULTICOLUMN)
    {
        INT col = (index / descr->page_size) -
                        (descr->top_item / descr->page_size);
        rect->left += col * descr->column_width;
        rect->right = rect->left + descr->column_width;
        rect->top += (index % descr->page_size) * descr->item_height;
        rect->bottom = rect->top + descr->item_height;
    }
    else if (descr->style & LBS_OWNERDRAWVARIABLE)
    {
        INT i;
        rect->right += descr->horz_pos;
        if ((index >= 0) && (index < descr->nb_items))
        {
            if (index < descr->top_item)
            {
                for (i = descr->top_item-1; i >= index; i--)
                    rect->top -= descr->items[i].height;
            }
            else
            {
                for (i = descr->top_item; i < index; i++)
                    rect->top += descr->items[i].height;
            }
            rect->bottom = rect->top + descr->items[index].height;

        }
    }
    else
    {
        rect->top += (index - descr->top_item) * descr->item_height;
        rect->bottom = rect->top + descr->item_height;
        rect->right += descr->horz_pos;
    }

    TRACE("item %d, rect %s\n", index, wine_dbgstr_rect(rect));

    return ((rect->left < descr->width) && (rect->right > 0) &&
            (rect->top < descr->height) && (rect->bottom > 0));
}