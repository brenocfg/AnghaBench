#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  orgWidths ;
typedef  int /*<<< orphan*/  orgPositions ;
struct TYPE_9__ {int cx; } ;
struct TYPE_13__ {int /*<<< orphan*/  hfont; TYPE_1__ spaceSize; } ;
struct TYPE_10__ {scalar_t__ bottom; scalar_t__ right; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_12__ {TYPE_2__ rcItem; int /*<<< orphan*/  hDC; int /*<<< orphan*/  hwndItem; scalar_t__ itemState; scalar_t__ itemAction; scalar_t__ itemID; scalar_t__ CtlID; scalar_t__ CtlType; } ;
struct TYPE_11__ {int* widths; int* positions; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_3__ Pane ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  Entry ;
typedef  TYPE_4__ DRAWITEMSTRUCT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int COLUMNS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 TYPE_8__ Globals ; 
 int IMAGE_WIDTH ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_GETCOUNT ; 
 int /*<<< orphan*/  LB_GETITEMDATA ; 
 int /*<<< orphan*/  LB_SETHORIZONTALEXTENT ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  draw_item (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static BOOL calc_widths(Pane* pane, BOOL anyway)
{
	int col, x, cx, spc=3*Globals.spaceSize.cx;
	int entries = SendMessageW(pane->hwnd, LB_GETCOUNT, 0, 0);
	int orgWidths[COLUMNS];
	int orgPositions[COLUMNS+1];
	HFONT hfontOld;
	HDC hdc;
	int cnt;

	if (!anyway) {
		memcpy(orgWidths, pane->widths, sizeof(orgWidths));
		memcpy(orgPositions, pane->positions, sizeof(orgPositions));
	}

	for(col=0; col<COLUMNS; col++)
		pane->widths[col] = 0;

	hdc = GetDC(pane->hwnd);
	hfontOld = SelectObject(hdc, Globals.hfont);

	for(cnt=0; cnt<entries; cnt++) {
		Entry* entry = (Entry*)SendMessageW(pane->hwnd, LB_GETITEMDATA, cnt, 0);

		DRAWITEMSTRUCT dis;

		dis.CtlType		  = 0;
		dis.CtlID		  = 0;
		dis.itemID		  = 0;
		dis.itemAction	  = 0;
		dis.itemState	  = 0;
		dis.hwndItem	  = pane->hwnd;
		dis.hDC			  = hdc;
		dis.rcItem.left	  = 0;
		dis.rcItem.top    = 0;
		dis.rcItem.right  = 0;
		dis.rcItem.bottom = 0;
		/*dis.itemData	  = 0; */

		draw_item(pane, &dis, entry, COLUMNS);
	}

	SelectObject(hdc, hfontOld);
	ReleaseDC(pane->hwnd, hdc);

	x = 0;
	for(col=0; col<COLUMNS; col++) {
		pane->positions[col] = x;
		cx = pane->widths[col];

		if (cx) {
			cx += spc;

			if (cx < IMAGE_WIDTH)
				cx = IMAGE_WIDTH;

			pane->widths[col] = cx;
		}

		x += cx;
	}

	pane->positions[COLUMNS] = x;

	SendMessageW(pane->hwnd, LB_SETHORIZONTALEXTENT, x, 0);

	/* no change? */
	if (!anyway && !memcmp(orgWidths, pane->widths, sizeof(orgWidths)))
		return FALSE;

	/* don't move, if only collapsing an entry */
	if (!anyway && pane->widths[0]<orgWidths[0] &&
		!memcmp(orgWidths+1, pane->widths+1, sizeof(orgWidths)-sizeof(int))) {
		pane->widths[0] = orgWidths[0];
		memcpy(pane->positions, orgPositions, sizeof(orgPositions));

		return FALSE;
	}

	InvalidateRect(pane->hwnd, 0, TRUE);

	return TRUE;
}