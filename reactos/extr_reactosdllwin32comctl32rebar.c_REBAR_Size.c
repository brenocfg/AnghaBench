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
typedef  int WPARAM ;
struct TYPE_5__ {int fStatus; int dwStyle; } ;
typedef  TYPE_1__ REBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int RBS_AUTOSIZE ; 
 int /*<<< orphan*/  REBAR_AutoSize (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REBAR_Layout (TYPE_1__*) ; 
 int SELF_RESIZE ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
REBAR_Size (REBAR_INFO *infoPtr, WPARAM wParam, LPARAM lParam)
{
    TRACE("wParam=%lx, lParam=%lx\n", wParam, lParam);

    /* avoid _Layout resize recursion (but it shouldn't be infinite and it seems Windows does recurse) */
    if (infoPtr->fStatus & SELF_RESIZE) {
	infoPtr->fStatus &= ~SELF_RESIZE;
	TRACE("SELF_RESIZE was set, reset, fStatus=%08x lparam=%08lx\n",
	      infoPtr->fStatus, lParam);
	return 0;
    }
    
    if (infoPtr->dwStyle & RBS_AUTOSIZE)
        REBAR_AutoSize(infoPtr, TRUE);
    else
        REBAR_Layout(infoPtr);

    return 0;
}