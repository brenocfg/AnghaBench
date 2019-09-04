#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_13__ {int /*<<< orphan*/  top; scalar_t__ left; } ;
struct TYPE_16__ {size_t itemID; int /*<<< orphan*/  CtlID; int /*<<< orphan*/  itemState; TYPE_1__ rcItem; int /*<<< orphan*/  itemData; int /*<<< orphan*/  hDC; int /*<<< orphan*/  itemAction; int /*<<< orphan*/  hwndItem; int /*<<< orphan*/  CtlType; } ;
struct TYPE_15__ {size_t nb_items; size_t focus_item; int style; scalar_t__ in_focus; scalar_t__ caret_on; int /*<<< orphan*/  tabs; int /*<<< orphan*/  nb_tabs; int /*<<< orphan*/  self; int /*<<< orphan*/  owner; TYPE_2__* items; } ;
struct TYPE_14__ {scalar_t__ selected; int /*<<< orphan*/ * str; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_2__ LB_ITEMDATA ;
typedef  TYPE_3__ LB_DESCR ;
typedef  size_t INT ;
typedef  scalar_t__ HRGN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_4__ DRAWITEMSTRUCT ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_HIGHLIGHT ; 
 int /*<<< orphan*/  COLOR_HIGHLIGHTTEXT ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  DrawFocusRect (int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/  ERR (char*,size_t,size_t) ; 
 int ETO_CLIPPED ; 
 int ETO_OPAQUE ; 
 int /*<<< orphan*/  ExtTextOutW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_OWNERDRAW (TYPE_3__*) ; 
 int /*<<< orphan*/  IsWindowEnabled (int /*<<< orphan*/ ) ; 
 int LBS_USETABSTOPS ; 
 int /*<<< orphan*/  ODA_FOCUS ; 
 int /*<<< orphan*/  ODS_DISABLED ; 
 int /*<<< orphan*/  ODS_FOCUS ; 
 int /*<<< orphan*/  ODS_SELECTED ; 
 int /*<<< orphan*/  ODT_LISTBOX ; 
 int /*<<< orphan*/  SelectClipRgn (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TabbedTextOutW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_DRAWITEM ; 
 char* debugstr_w (int /*<<< orphan*/ *) ; 
 scalar_t__ set_control_clipping (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  strlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_1__ const*) ; 

__attribute__((used)) static void LISTBOX_PaintItem( LB_DESCR *descr, HDC hdc, const RECT *rect,
			       INT index, UINT action, BOOL ignoreFocus )
{
    LB_ITEMDATA *item = NULL;
    if (index < descr->nb_items) item = &descr->items[index];

    if (IS_OWNERDRAW(descr))
    {
        DRAWITEMSTRUCT dis;
        RECT r;
        HRGN hrgn;

	if (!item)
	{
	    if (action == ODA_FOCUS)
		DrawFocusRect( hdc, rect );
	    else
	        ERR("called with an out of bounds index %d(%d) in owner draw, Not good.\n",index,descr->nb_items);
	    return;
	}

        /* some programs mess with the clipping region when
        drawing the item, *and* restore the previous region
        after they are done, so a region has better to exist
        else everything ends clipped */
        GetClientRect(descr->self, &r);
        hrgn = set_control_clipping( hdc, &r );

        dis.CtlType      = ODT_LISTBOX;
        dis.CtlID        = GetWindowLongPtrW( descr->self, GWLP_ID );
        dis.hwndItem     = descr->self;
        dis.itemAction   = action;
        dis.hDC          = hdc;
        dis.itemID       = index;
        dis.itemState    = 0;
        if (item->selected) dis.itemState |= ODS_SELECTED;
        if (!ignoreFocus && (descr->focus_item == index) &&
            (descr->caret_on) &&
            (descr->in_focus)) dis.itemState |= ODS_FOCUS;
        if (!IsWindowEnabled(descr->self)) dis.itemState |= ODS_DISABLED;
        dis.itemData     = item->data;
        dis.rcItem       = *rect;
        TRACE("[%p]: drawitem %d (%s) action=%02x state=%02x rect=%s\n",
              descr->self, index, debugstr_w(item->str), action,
              dis.itemState, wine_dbgstr_rect(rect) );
        SendMessageW(descr->owner, WM_DRAWITEM, dis.CtlID, (LPARAM)&dis);
        SelectClipRgn( hdc, hrgn );
        if (hrgn) DeleteObject( hrgn );
    }
    else
    {
        COLORREF oldText = 0, oldBk = 0;

        if (action == ODA_FOCUS)
        {
            DrawFocusRect( hdc, rect );
            return;
        }
        if (item && item->selected)
        {
            oldBk = SetBkColor( hdc, GetSysColor( COLOR_HIGHLIGHT ) );
            oldText = SetTextColor( hdc, GetSysColor(COLOR_HIGHLIGHTTEXT));
        }

        TRACE("[%p]: painting %d (%s) action=%02x rect=%s\n",
              descr->self, index, item ? debugstr_w(item->str) : "", action,
              wine_dbgstr_rect(rect) );
        if (!item)
            ExtTextOutW( hdc, rect->left + 1, rect->top,
                           ETO_OPAQUE | ETO_CLIPPED, rect, NULL, 0, NULL );
        else if (!(descr->style & LBS_USETABSTOPS))
            ExtTextOutW( hdc, rect->left + 1, rect->top,
                         ETO_OPAQUE | ETO_CLIPPED, rect, item->str,
                         strlenW(item->str), NULL );
        else
	{
	    /* Output empty string to paint background in the full width. */
            ExtTextOutW( hdc, rect->left + 1, rect->top,
                         ETO_OPAQUE | ETO_CLIPPED, rect, NULL, 0, NULL );
            TabbedTextOutW( hdc, rect->left + 1 , rect->top,
                            item->str, strlenW(item->str),
                            descr->nb_tabs, descr->tabs, 0);
	}
        if (item && item->selected)
        {
            SetBkColor( hdc, oldBk );
            SetTextColor( hdc, oldText );
        }
        if (!ignoreFocus && (descr->focus_item == index) &&
            (descr->caret_on) &&
            (descr->in_focus)) DrawFocusRect( hdc, rect );
    }
}