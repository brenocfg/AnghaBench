#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int dwStyle; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_9__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ REBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HTHEME ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  BDR_RAISEDINNER ; 
 int /*<<< orphan*/  BF_RECT ; 
 int /*<<< orphan*/  BF_TOP ; 
 int DCX_USESTYLE ; 
 int DCX_WINDOW ; 
 int /*<<< orphan*/  DrawEdge (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawThemeEdge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDGE_ETCHED ; 
 int /*<<< orphan*/  GetDCEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int WS_BORDER ; 
 int WS_MINIMIZE ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static LRESULT
REBAR_NCPaint (const REBAR_INFO *infoPtr)
{
    RECT rcWindow;
    HDC hdc;
    HTHEME theme;

    if (infoPtr->dwStyle & WS_MINIMIZE)
	return 0; /* Nothing to do */

    if (infoPtr->dwStyle & WS_BORDER) {

	/* adjust rectangle and draw the necessary edge */
	if (!(hdc = GetDCEx( infoPtr->hwndSelf, 0, DCX_USESTYLE | DCX_WINDOW )))
	    return 0;
	GetWindowRect (infoPtr->hwndSelf, &rcWindow);
	OffsetRect (&rcWindow, -rcWindow.left, -rcWindow.top);
        TRACE("rect (%s)\n", wine_dbgstr_rect(&rcWindow));
	DrawEdge (hdc, &rcWindow, EDGE_ETCHED, BF_RECT);
	ReleaseDC( infoPtr->hwndSelf, hdc );
    }
    else if ((theme = GetWindowTheme (infoPtr->hwndSelf)))
    {
        /* adjust rectangle and draw the necessary edge */
        if (!(hdc = GetDCEx( infoPtr->hwndSelf, 0, DCX_USESTYLE | DCX_WINDOW )))
            return 0;
        GetWindowRect (infoPtr->hwndSelf, &rcWindow);
        OffsetRect (&rcWindow, -rcWindow.left, -rcWindow.top);
        TRACE("rect (%s)\n", wine_dbgstr_rect(&rcWindow));
        DrawThemeEdge (theme, hdc, 0, 0, &rcWindow, BDR_RAISEDINNER, BF_TOP, NULL);
        ReleaseDC( infoPtr->hwndSelf, hdc );
    }

    return 0;
}