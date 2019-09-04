#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  IOleCommandTarget_iface; } ;
struct TYPE_9__ {TYPE_1__ basedoc; int /*<<< orphan*/  hwnd; scalar_t__ hostui; } ;
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  TYPE_3__ HTMLDocumentObj ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CGID_MSHTML ; 
 int /*<<< orphan*/  DestroyMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSubMenu (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IDR_BROWSE_CONTEXT_MENU ; 
 scalar_t__ IDocHostUIHandler_ShowContextMenu (scalar_t__,scalar_t__,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleCommandTarget_Exec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LoadMenuW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int TPM_LEFTALIGN ; 
 int TPM_RETURNCMD ; 
 int TPM_RIGHTBUTTON ; 
 scalar_t__ TrackPopupMenu (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_shdoclc () ; 

void show_context_menu(HTMLDocumentObj *This, DWORD dwID, POINT *ppt, IDispatch *elem)
{
    HMENU menu_res, menu;
    DWORD cmdid;

    if(This->hostui && S_OK == IDocHostUIHandler_ShowContextMenu(This->hostui,
            dwID, ppt, (IUnknown*)&This->basedoc.IOleCommandTarget_iface, elem))
        return;

    menu_res = LoadMenuW(get_shdoclc(), MAKEINTRESOURCEW(IDR_BROWSE_CONTEXT_MENU));
    menu = GetSubMenu(menu_res, dwID);

    cmdid = TrackPopupMenu(menu, TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD,
            ppt->x, ppt->y, 0, This->hwnd, NULL);
    DestroyMenu(menu_res);

    if(cmdid)
        IOleCommandTarget_Exec(&This->basedoc.IOleCommandTarget_iface, &CGID_MSHTML, cmdid, 0,
                NULL, NULL);
}