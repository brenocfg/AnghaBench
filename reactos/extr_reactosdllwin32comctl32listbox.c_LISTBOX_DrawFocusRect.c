#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int focus_item; int /*<<< orphan*/  self; int /*<<< orphan*/  horz_pos; scalar_t__ font; int /*<<< orphan*/  in_focus; int /*<<< orphan*/  caret_on; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ LB_DESCR ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_GRAYTEXT ; 
 int /*<<< orphan*/  DCX_CACHE ; 
 int /*<<< orphan*/  GetDCEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindowEnabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindowVisible (int /*<<< orphan*/ ) ; 
 int LISTBOX_GetItemRect (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LISTBOX_PaintItem (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ODA_FOCUS ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowOrgEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void LISTBOX_DrawFocusRect( LB_DESCR *descr, BOOL on )
{
    HDC hdc;
    RECT rect;
    HFONT oldFont = 0;

    /* Do not repaint the item if the item is not visible */
    if (!IsWindowVisible(descr->self)) return;

    if (descr->focus_item == -1) return;
    if (!descr->caret_on || !descr->in_focus) return;

    if (LISTBOX_GetItemRect( descr, descr->focus_item, &rect ) != 1) return;
    if (!(hdc = GetDCEx( descr->self, 0, DCX_CACHE ))) return;
    if (descr->font) oldFont = SelectObject( hdc, descr->font );
    if (!IsWindowEnabled(descr->self))
        SetTextColor( hdc, GetSysColor( COLOR_GRAYTEXT ) );
    SetWindowOrgEx( hdc, descr->horz_pos, 0, NULL );
    LISTBOX_PaintItem( descr, hdc, &rect, descr->focus_item, ODA_FOCUS, !on );
    if (oldFont) SelectObject( hdc, oldFont );
    ReleaseDC( descr->self, hdc );
}