#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  id; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_3__ customctrl ;
typedef  scalar_t__ UINT ;
struct TYPE_22__ {int /*<<< orphan*/  dlg_hwnd; } ;
struct TYPE_17__ {int /*<<< orphan*/  bottom; } ;
struct TYPE_16__ {int /*<<< orphan*/  hwndFrom; } ;
struct TYPE_21__ {TYPE_2__ rcButton; TYPE_1__ hdr; } ;
struct TYPE_20__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {scalar_t__ dwData; } ;
typedef  TYPE_4__ TBBUTTON ;
typedef  TYPE_5__ POINT ;
typedef  TYPE_6__ NMTOOLBARW ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  TYPE_7__ FileDialogImpl ;

/* Variables and functions */
 int /*<<< orphan*/  ClientToScreen (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  GetDlgCtrlID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TBDDRET_DEFAULT ; 
 int /*<<< orphan*/  TB_GETBUTTON ; 
 int /*<<< orphan*/  TPM_RETURNCMD ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_7__*,TYPE_3__*,scalar_t__) ; 
 scalar_t__ TrackPopupMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cctrl_event_OnControlActivating (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cctrl_event_OnItemSelected (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* get_cctrl_from_dlgid (TYPE_7__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT notifysink_on_tvn_dropdown(FileDialogImpl *This, LPARAM lparam)
{
    NMTOOLBARW *nmtb = (NMTOOLBARW*)lparam;
    customctrl *ctrl = get_cctrl_from_dlgid(This, GetDlgCtrlID(nmtb->hdr.hwndFrom));
    POINT pt = { 0, nmtb->rcButton.bottom };
    TBBUTTON tbb;
    UINT idcmd;

    TRACE("%p, %p (%lx)\n", This, ctrl, lparam);

    if(ctrl)
    {
        cctrl_event_OnControlActivating(This,ctrl->id);

        SendMessageW(ctrl->hwnd, TB_GETBUTTON, 0, (LPARAM)&tbb);
        ClientToScreen(ctrl->hwnd, &pt);
        idcmd = TrackPopupMenu((HMENU)tbb.dwData, TPM_RETURNCMD, pt.x, pt.y, 0, This->dlg_hwnd, NULL);
        if(idcmd)
            cctrl_event_OnItemSelected(This, ctrl->id, idcmd);
    }

    return TBDDRET_DEFAULT;
}