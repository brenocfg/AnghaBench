#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int /*<<< orphan*/  hInstance; } ;
struct TYPE_6__ {int mask; int fmt; int /*<<< orphan*/  cxy; int /*<<< orphan*/  pszText; } ;
struct TYPE_5__ {int /*<<< orphan*/ * widths; } ;
typedef  TYPE_1__ Pane ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  TYPE_2__ HDITEMW ;

/* Variables and functions */
 int COLUMNS ; 
 int /*<<< orphan*/  CreateWindowW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFAULT_GUI_FONT ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 TYPE_4__ Globals ; 
 int HDF_STRING ; 
 int HDI_FORMAT ; 
 int HDI_TEXT ; 
 int HDI_WIDTH ; 
 int /*<<< orphan*/  HDM_INSERTITEMW ; 
 int HDS_FULLDRAG ; 
 int HDS_HORZ ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ULongToHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WC_HEADERW ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 
 int* g_pos_align ; 
 int /*<<< orphan*/ * g_pos_names ; 

__attribute__((used)) static HWND create_header(HWND parent, Pane* pane, UINT id)
{
	HDITEMW hdi;
	int idx;

	HWND hwnd = CreateWindowW(WC_HEADERW, 0, WS_CHILD|WS_VISIBLE|HDS_HORZ|HDS_FULLDRAG/*TODO: |HDS_BUTTONS + sort orders*/,
                                 0, 0, 0, 0, parent, (HMENU)ULongToHandle(id), Globals.hInstance, 0);
	if (!hwnd)
		return 0;

	SendMessageW(hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), FALSE);

	hdi.mask = HDI_TEXT|HDI_WIDTH|HDI_FORMAT;

	for(idx=0; idx<COLUMNS; idx++) {
		hdi.pszText = g_pos_names[idx];
		hdi.fmt = HDF_STRING | g_pos_align[idx];
		hdi.cxy = pane->widths[idx];
		SendMessageW(hwnd, HDM_INSERTITEMW, idx, (LPARAM)&hdi);
	}

	return hwnd;
}