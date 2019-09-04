#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_13__ {int style; int selected_item; int anchor_item; int item_height; int page_size; int column_width; int caret_on; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  owner; int /*<<< orphan*/  self; TYPE_3__* lphc; int /*<<< orphan*/  locale; scalar_t__ font; void* captured; void* in_focus; scalar_t__ wheel_remain; int /*<<< orphan*/ * tabs; scalar_t__ nb_tabs; scalar_t__ horz_pos; scalar_t__ horz_extent; scalar_t__ focus_item; scalar_t__ top_item; scalar_t__ nb_items; int /*<<< orphan*/ * items; } ;
struct TYPE_12__ {int dwStyle; int fixedOwnerDrawHeight; int /*<<< orphan*/  self; } ;
struct TYPE_11__ {int itemID; int itemHeight; scalar_t__ itemData; scalar_t__ itemWidth; int /*<<< orphan*/  CtlID; int /*<<< orphan*/  CtlType; } ;
struct TYPE_10__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ MEASUREITEMSTRUCT ;
typedef  TYPE_3__* LPHEADCOMBO ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  TYPE_4__ LB_DESCR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  void* BOOL ;

/* Variables and functions */
 int CBS_DROPDOWN ; 
 void* FALSE ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetUserDefaultLCID () ; 
 int GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int LBS_EXTENDEDSEL ; 
 int LBS_HASSTRINGS ; 
 int LBS_MULTICOLUMN ; 
 int LBS_MULTIPLESEL ; 
 int LBS_NODATA ; 
 int LBS_NOINTEGRALHEIGHT ; 
 int LBS_NOSEL ; 
 int LBS_OWNERDRAWFIXED ; 
 int LBS_OWNERDRAWVARIABLE ; 
 int LBS_SORT ; 
 int LISTBOX_SetFont (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTBOX_update_uistate (TYPE_4__*) ; 
 int /*<<< orphan*/  ODT_LISTBOX ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int,scalar_t__,...) ; 
 void* TRUE ; 
 int /*<<< orphan*/  WM_MEASUREITEM ; 

__attribute__((used)) static BOOL LISTBOX_Create( HWND hwnd, LPHEADCOMBO lphc )
{
    LB_DESCR *descr;
    MEASUREITEMSTRUCT mis;
    RECT rect;

    if (!(descr = HeapAlloc( GetProcessHeap(), 0, sizeof(*descr) )))
        return FALSE;

    GetClientRect( hwnd, &rect );
    descr->self          = hwnd;
    descr->owner         = GetParent( descr->self );
    descr->style         = GetWindowLongPtrW( descr->self, GWL_STYLE );
    descr->width         = rect.right - rect.left;
    descr->height        = rect.bottom - rect.top;
    descr->items         = NULL;
    descr->nb_items      = 0;
    descr->top_item      = 0;
    descr->selected_item = -1;
    descr->focus_item    = 0;
    descr->anchor_item   = -1;
    descr->item_height   = 1;
    descr->page_size     = 1;
    descr->column_width  = 150;
    descr->horz_extent   = 0;
    descr->horz_pos      = 0;
    descr->nb_tabs       = 0;
    descr->tabs          = NULL;
    descr->wheel_remain  = 0;
    descr->caret_on      = !lphc;
    if (descr->style & LBS_NOSEL) descr->caret_on = FALSE;
    descr->in_focus 	 = FALSE;
    descr->captured      = FALSE;
    descr->font          = 0;
    descr->locale        = GetUserDefaultLCID();
    descr->lphc		 = lphc;

    if( lphc )
    {
        TRACE("[%p]: resetting owner %p -> %p\n", descr->self, descr->owner, lphc->self );
        descr->owner = lphc->self;
    }

    SetWindowLongPtrW( descr->self, 0, (LONG_PTR)descr );

    LISTBOX_update_uistate(descr); // ReactOS

/*    if (wnd->dwExStyle & WS_EX_NOPARENTNOTIFY) descr->style &= ~LBS_NOTIFY;
 */
    if (descr->style & LBS_EXTENDEDSEL) descr->style |= LBS_MULTIPLESEL;
    if (descr->style & LBS_MULTICOLUMN) descr->style &= ~LBS_OWNERDRAWVARIABLE;
    if (descr->style & LBS_OWNERDRAWVARIABLE) descr->style |= LBS_NOINTEGRALHEIGHT;

    //// ReactOS
    /* A no-data list box must also have the LBS_OWNERDRAWFIXED style, but must
       not have the LBS_SORT or LBS_HASSTRINGS style. */
    if ( descr->style & LBS_NODATA &&
        (!(descr->style & LBS_OWNERDRAWFIXED) || descr->style & (LBS_HASSTRINGS|LBS_SORT) ) )
       descr->style &= ~LBS_NODATA;
    ////
    descr->item_height = LISTBOX_SetFont( descr, 0 );

    if (descr->style & LBS_OWNERDRAWFIXED)
    {
	if( descr->lphc && (descr->lphc->dwStyle & CBS_DROPDOWN))
	{
	    /* WinWord gets VERY unhappy if we send WM_MEASUREITEM from here */
	  descr->item_height = lphc->fixedOwnerDrawHeight;
	}
	else
	{
            UINT id = (UINT)GetWindowLongPtrW( descr->self, GWLP_ID );
            mis.CtlType    = ODT_LISTBOX;
            mis.CtlID      = id;
            mis.itemID     = -1;
            mis.itemWidth  =  0;
            mis.itemData   =  0;
            mis.itemHeight = descr->item_height;
            SendMessageW( descr->owner, WM_MEASUREITEM, id, (LPARAM)&mis );
            descr->item_height = mis.itemHeight ? mis.itemHeight : 1;
	}
    }

    TRACE("owner: %p, style: %08x, width: %d, height: %d\n", descr->owner, descr->style, descr->width, descr->height);
    return TRUE;
}