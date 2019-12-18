#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ left; scalar_t__ top; scalar_t__ right; scalar_t__ bottom; } ;
struct TYPE_20__ {int flags; int style; scalar_t__ y_offset; scalar_t__ line_count; int /*<<< orphan*/  hwndSelf; scalar_t__ font; scalar_t__ bEnableState; TYPE_1__ format_rect; } ;
struct TYPE_19__ {scalar_t__ left; scalar_t__ top; scalar_t__ right; scalar_t__ bottom; } ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HFONT ;
typedef  scalar_t__ HDC ;
typedef  scalar_t__ HBRUSH ;
typedef  TYPE_3__ EDITSTATE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ BeginPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COLOR_GRAYTEXT ; 
 int /*<<< orphan*/  COLOR_WINDOWFRAME ; 
 int /*<<< orphan*/  EDIT_GetLineRect (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  EDIT_InvalidateUniscribeData (TYPE_3__*) ; 
 scalar_t__ EDIT_NotifyCtlColor (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  EDIT_PaintLine (TYPE_3__*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  EDIT_UpdateUniscribeData (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int EF_FOCUSED ; 
 int ES_MULTILINE ; 
 int ES_NOHIDESEL ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FillRect (scalar_t__,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetClipBox (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  GetSysColor (int /*<<< orphan*/ ) ; 
 scalar_t__ GetSysColorBrush (int /*<<< orphan*/ ) ; 
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IntersectClipRect (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ IntersectRect (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  PATCOPY ; 
 int /*<<< orphan*/  PatBlt (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXBORDER ; 
 int /*<<< orphan*/  SM_CYBORDER ; 
 scalar_t__ SelectObject (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SetTextColor (scalar_t__,int /*<<< orphan*/ ) ; 
 int WS_BORDER ; 
 int WS_HSCROLL ; 
 int WS_VSCROLL ; 
 scalar_t__ get_vertical_line_count (TYPE_3__*) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void EDIT_WM_Paint(EDITSTATE *es, HDC hdc)
{
	PAINTSTRUCT ps;
	INT i;
	HDC dc;
	HFONT old_font = 0;
	RECT rc;
	RECT rcClient;
	RECT rcLine;
	RECT rcRgn;
	HBRUSH brush;
	HBRUSH old_brush;
	INT bw, bh;
	BOOL rev = es->bEnableState &&
				((es->flags & EF_FOCUSED) ||
					(es->style & ES_NOHIDESEL));
        dc = hdc ? hdc : BeginPaint(es->hwndSelf, &ps);

	/* The dc we use for calculating may not be the one we paint into.
	   This is the safest action. */
	EDIT_InvalidateUniscribeData(es);
	GetClientRect(es->hwndSelf, &rcClient);

	/* get the background brush */
	brush = EDIT_NotifyCtlColor(es, dc);

	/* paint the border and the background */
	IntersectClipRect(dc, rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
	
	if(es->style & WS_BORDER) {
		bw = GetSystemMetrics(SM_CXBORDER);
		bh = GetSystemMetrics(SM_CYBORDER);
		rc = rcClient;
		if(es->style & ES_MULTILINE) {
			if(es->style & WS_HSCROLL) rc.bottom+=bh;
			if(es->style & WS_VSCROLL) rc.right+=bw;
		}
		
		/* Draw the frame. Same code as in nonclient.c */
		old_brush = SelectObject(dc, GetSysColorBrush(COLOR_WINDOWFRAME));
		PatBlt(dc, rc.left, rc.top, rc.right - rc.left, bh, PATCOPY);
		PatBlt(dc, rc.left, rc.top, bw, rc.bottom - rc.top, PATCOPY);
		PatBlt(dc, rc.left, rc.bottom - 1, rc.right - rc.left, -bw, PATCOPY);
		PatBlt(dc, rc.right - 1, rc.top, -bw, rc.bottom - rc.top, PATCOPY);
		SelectObject(dc, old_brush);
		
		/* Keep the border clean */
		IntersectClipRect(dc, rc.left+bw, rc.top+bh,
		    max(rc.right-bw, rc.left+bw), max(rc.bottom-bh, rc.top+bh));
	}
	
	GetClipBox(dc, &rc);
	FillRect(dc, &rc, brush);

	IntersectClipRect(dc, es->format_rect.left,
				es->format_rect.top,
				es->format_rect.right,
				es->format_rect.bottom);
	if (es->style & ES_MULTILINE) {
		rc = rcClient;
		IntersectClipRect(dc, rc.left, rc.top, rc.right, rc.bottom);
	}
	if (es->font)
		old_font = SelectObject(dc, es->font);

	if (!es->bEnableState)
		SetTextColor(dc, GetSysColor(COLOR_GRAYTEXT));
	GetClipBox(dc, &rcRgn);
	if (es->style & ES_MULTILINE) {
		INT vlc = get_vertical_line_count(es);
		for (i = es->y_offset ; i <= min(es->y_offset + vlc, es->y_offset + es->line_count - 1) ; i++) {
			EDIT_UpdateUniscribeData(es, dc, i);
			EDIT_GetLineRect(es, i, 0, -1, &rcLine);
			if (IntersectRect(&rc, &rcRgn, &rcLine))
				EDIT_PaintLine(es, dc, i, rev);
		}
	} else {
		EDIT_UpdateUniscribeData(es, dc, 0);
		EDIT_GetLineRect(es, 0, 0, -1, &rcLine);
		if (IntersectRect(&rc, &rcRgn, &rcLine))
			EDIT_PaintLine(es, dc, 0, rev);
	}
	if (es->font)
		SelectObject(dc, old_font);

        if (!hdc)
            EndPaint(es->hwndSelf, &ps);
}