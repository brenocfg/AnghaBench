#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
typedef  TYPE_1__* LPWINDOWPOS ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  IsIconic (int /*<<< orphan*/ ) ; 
 int SWP_NOSIZE ; 
 int /*<<< orphan*/  gui_mswin_get_valid_dimensions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
_OnWindowPosChanging(
    HWND hwnd,
    LPWINDOWPOS lpwpos)
{

    if (!IsIconic(hwnd) && !(lpwpos->flags & SWP_NOSIZE))
    {
	gui_mswin_get_valid_dimensions(lpwpos->cx, lpwpos->cy,
				     &lpwpos->cx, &lpwpos->cy);
    }
    return 0;
}