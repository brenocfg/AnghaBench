#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  REBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  REBAR_SizeToHeight (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_rect_cy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static LRESULT
#ifdef __REACTOS__
REBAR_SizeToRect (REBAR_INFO *infoPtr, WPARAM flags, RECT *lpRect)
#else
REBAR_SizeToRect (REBAR_INFO *infoPtr, const RECT *lpRect)
#endif
{
    if (!lpRect) return FALSE;

    TRACE("[%s]\n", wine_dbgstr_rect(lpRect));
    REBAR_SizeToHeight(infoPtr, get_rect_cy(infoPtr, lpRect));

#ifdef __REACTOS__
    /* Note that this undocumented flag is available on comctl32 v6 or later */
    if ((flags & RBSTR_CHANGERECT) != 0)
    {
        RECT rcRebar;
        GetClientRect(infoPtr->hwndSelf, &rcRebar);
        lpRect->bottom = lpRect->top + (rcRebar.bottom - rcRebar.top);
    }
#endif
    return TRUE;
}