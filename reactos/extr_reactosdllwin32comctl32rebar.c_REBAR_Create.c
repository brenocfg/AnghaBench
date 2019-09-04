#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {int /*<<< orphan*/  dwStyle; int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__* LPCREATESTRUCTW ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ OpenThemeData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WS_BORDER ; 
 int /*<<< orphan*/  rebar ; 
 int /*<<< orphan*/  themeClass ; 
 int /*<<< orphan*/  wine_dbgstr_rect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LRESULT
REBAR_Create (REBAR_INFO *infoPtr, LPCREATESTRUCTW cs)
{
    RECT wnrc1, clrc1;

    if (TRACE_ON(rebar)) {
	GetWindowRect(infoPtr->hwndSelf, &wnrc1);
	GetClientRect(infoPtr->hwndSelf, &clrc1);
        TRACE("window=(%s) client=(%s) cs=(%d,%d %dx%d)\n",
              wine_dbgstr_rect(&wnrc1), wine_dbgstr_rect(&clrc1),
	      cs->x, cs->y, cs->cx, cs->cy);
    }

    TRACE("created!\n");

    if (OpenThemeData (infoPtr->hwndSelf, themeClass))
    {
        /* native seems to clear WS_BORDER when themed */
        infoPtr->dwStyle &= ~WS_BORDER;
    }

    return 0;
}