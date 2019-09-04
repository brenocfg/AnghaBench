#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int cxy; int /*<<< orphan*/  mask; } ;
struct TYPE_19__ {int iItem; TYPE_1__* pitem; } ;
struct TYPE_18__ {int code; } ;
struct TYPE_17__ {int* widths; int* positions; int /*<<< orphan*/  hwnd; int /*<<< orphan*/  hwndHeader; } ;
struct TYPE_16__ {int right; int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; } ;
struct TYPE_15__ {int cxy; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ Pane ;
typedef  TYPE_4__ NMHDR ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_5__* LPNMHEADERW ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_6__ HDITEMW ;

/* Variables and functions */
 int COLUMNS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int GetScrollPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDI_WIDTH ; 
 int /*<<< orphan*/  HDM_SETITEMW ; 
#define  HDN_DIVIDERDBLCLICKW 129 
 int HDN_ENDTRACKW ; 
#define  HDN_ITEMCHANGEDW 128 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_SETHORIZONTALEXTENT ; 
 int RDW_INVALIDATE ; 
 int RDW_UPDATENOW ; 
 int /*<<< orphan*/  RedrawWindow (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SB_HORZ ; 
 int /*<<< orphan*/  SW_INVALIDATE ; 
 int /*<<< orphan*/  ScrollWindowEx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  calc_single_width (TYPE_3__*,int) ; 
 int /*<<< orphan*/  set_header (TYPE_3__*) ; 

__attribute__((used)) static LRESULT pane_notify(Pane* pane, NMHDR* pnmh)
{
	switch(pnmh->code) {
		case HDN_ITEMCHANGEDW: {
			LPNMHEADERW phdn = (LPNMHEADERW)pnmh;
			int idx = phdn->iItem;
			int dx = phdn->pitem->cxy - pane->widths[idx];
			int i;

			RECT clnt;
			GetClientRect(pane->hwnd, &clnt);

			pane->widths[idx] += dx;

			for(i=idx; ++i<=COLUMNS; )
				pane->positions[i] += dx;

			{
				int scroll_pos = GetScrollPos(pane->hwnd, SB_HORZ);
				RECT rt_scr;
				RECT rt_clip;

				rt_scr.left   = pane->positions[idx+1]-scroll_pos;
				rt_scr.top    = 0;
				rt_scr.right  = clnt.right;
				rt_scr.bottom = clnt.bottom;

				rt_clip.left   = pane->positions[idx]-scroll_pos;
				rt_clip.top    = 0;
				rt_clip.right  = clnt.right;
				rt_clip.bottom = clnt.bottom;

				if (rt_scr.left < 0) rt_scr.left = 0;
				if (rt_clip.left < 0) rt_clip.left = 0;

				ScrollWindowEx(pane->hwnd, dx, 0, &rt_scr, &rt_clip, 0, 0, SW_INVALIDATE);

				rt_clip.right = pane->positions[idx+1];
				RedrawWindow(pane->hwnd, &rt_clip, 0, RDW_INVALIDATE|RDW_UPDATENOW);

				if (pnmh->code == HDN_ENDTRACKW) {
					SendMessageW(pane->hwnd, LB_SETHORIZONTALEXTENT, pane->positions[COLUMNS], 0);

					if (GetScrollPos(pane->hwnd, SB_HORZ) != scroll_pos)
						set_header(pane);
				}
			}

			return FALSE;
		}

		case HDN_DIVIDERDBLCLICKW: {
			LPNMHEADERW phdn = (LPNMHEADERW)pnmh;
			HDITEMW item;

			calc_single_width(pane, phdn->iItem);
			item.mask = HDI_WIDTH;
			item.cxy = pane->widths[phdn->iItem];

			SendMessageW(pane->hwndHeader, HDM_SETITEMW, phdn->iItem, (LPARAM)&item);
			InvalidateRect(pane->hwnd, 0, TRUE);
			break;}
	}

	return 0;
}