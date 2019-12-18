#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_12__ {size_t page_size; int style; scalar_t__ height; size_t nb_items; int focus_item; scalar_t__ item_height; size_t top_item; scalar_t__ width; scalar_t__ in_focus; scalar_t__ caret_on; scalar_t__ column_width; TYPE_1__* items; scalar_t__ self; int /*<<< orphan*/  owner; scalar_t__ font; scalar_t__ horz_pos; } ;
struct TYPE_11__ {int member_0; int member_1; int member_2; int member_3; scalar_t__ bottom; scalar_t__ top; scalar_t__ right; scalar_t__ left; } ;
struct TYPE_10__ {scalar_t__ height; } ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_3__ LB_DESCR ;
typedef  size_t INT ;
typedef  scalar_t__ HFONT ;
typedef  scalar_t__ HDC ;
typedef  scalar_t__ HBRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_GRAYTEXT ; 
 int ETO_CLIPPED ; 
 int ETO_OPAQUE ; 
 int /*<<< orphan*/  ExtTextOutW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetControlColor (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_OWNERDRAW (TYPE_3__*) ; 
 int /*<<< orphan*/  IsWindowEnabled (scalar_t__) ; 
 int LBS_MULTICOLUMN ; 
 int LBS_NOREDRAW ; 
 int LBS_OWNERDRAWVARIABLE ; 
 int /*<<< orphan*/  LISTBOX_PaintItem (TYPE_3__*,scalar_t__,TYPE_2__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ODA_DRAWENTIRE ; 
 int /*<<< orphan*/  ODA_FOCUS ; 
 scalar_t__ SelectObject (scalar_t__,scalar_t__) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SetTextColor (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowOrgEx (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_CTLCOLORLISTBOX ; 

__attribute__((used)) static LRESULT LISTBOX_Paint( LB_DESCR *descr, HDC hdc )
{
    INT i, col_pos = descr->page_size - 1;
    RECT rect;
    RECT focusRect = {-1, -1, -1, -1};
    HFONT oldFont = 0;
    HBRUSH hbrush, oldBrush = 0;

    if (descr->style & LBS_NOREDRAW) return 0;

    SetRect( &rect, 0, 0, descr->width, descr->height );
    if (descr->style & LBS_MULTICOLUMN)
        rect.right = rect.left + descr->column_width;
    else if (descr->horz_pos)
    {
        SetWindowOrgEx( hdc, descr->horz_pos, 0, NULL );
        rect.right += descr->horz_pos;
    }

    if (descr->font) oldFont = SelectObject( hdc, descr->font );
#ifdef __REACTOS__
    hbrush = GetControlColor( descr->owner, descr->self, hdc, WM_CTLCOLORLISTBOX);
#else
    hbrush = (HBRUSH)SendMessageW( descr->owner, WM_CTLCOLORLISTBOX,
			   	   (WPARAM)hdc, (LPARAM)descr->self );
#endif
    if (hbrush) oldBrush = SelectObject( hdc, hbrush );
    if (!IsWindowEnabled(descr->self)) SetTextColor( hdc, GetSysColor( COLOR_GRAYTEXT ) );

    if (!descr->nb_items && (descr->focus_item != -1) && descr->caret_on &&
        (descr->in_focus))
    {
        /* Special case for empty listbox: paint focus rect */
        rect.bottom = rect.top + descr->item_height;
        ExtTextOutW( hdc, 0, 0, ETO_OPAQUE | ETO_CLIPPED,
                     &rect, NULL, 0, NULL );
        LISTBOX_PaintItem( descr, hdc, &rect, descr->focus_item, ODA_FOCUS, FALSE );
        rect.top = rect.bottom;
    }

    /* Paint all the item, regarding the selection
       Focus state will be painted after  */

    for (i = descr->top_item; i < descr->nb_items; i++)
    {
        if (!(descr->style & LBS_OWNERDRAWVARIABLE))
            rect.bottom = rect.top + descr->item_height;
        else
            rect.bottom = rect.top + descr->items[i].height;

        /* keep the focus rect, to paint the focus item after */
        if (i == descr->focus_item)
            focusRect = rect;
    
        LISTBOX_PaintItem( descr, hdc, &rect, i, ODA_DRAWENTIRE, TRUE );
        rect.top = rect.bottom;

        if ((descr->style & LBS_MULTICOLUMN) && !col_pos)
        {
            if (!IS_OWNERDRAW(descr))
            {
                /* Clear the bottom of the column */
                if (rect.top < descr->height)
                {
                    rect.bottom = descr->height;
                    ExtTextOutW( hdc, 0, 0, ETO_OPAQUE | ETO_CLIPPED,
                                   &rect, NULL, 0, NULL );
                }
            }

            /* Go to the next column */
            rect.left += descr->column_width;
            rect.right += descr->column_width;
            rect.top = 0;
            col_pos = descr->page_size - 1;
        }
        else
        {
            col_pos--;
            if (rect.top >= descr->height) break;
        }
    }

    /* Paint the focus item now */
    if (focusRect.top != focusRect.bottom &&
        descr->caret_on && descr->in_focus)
        LISTBOX_PaintItem( descr, hdc, &focusRect, descr->focus_item, ODA_FOCUS, FALSE );

    if (!IS_OWNERDRAW(descr))
    {
        /* Clear the remainder of the client area */
        if (rect.top < descr->height)
        {
            rect.bottom = descr->height;
            ExtTextOutW( hdc, 0, 0, ETO_OPAQUE | ETO_CLIPPED,
                           &rect, NULL, 0, NULL );
        }
        if (rect.right < descr->width)
        {
            rect.left   = rect.right;
            rect.right  = descr->width;
            rect.top    = 0;
            rect.bottom = descr->height;
            ExtTextOutW( hdc, 0, 0, ETO_OPAQUE | ETO_CLIPPED,
                           &rect, NULL, 0, NULL );
        }
    }
    if (oldFont) SelectObject( hdc, oldFont );
    if (oldBrush) SelectObject( hdc, oldBrush );
    return 0;
}