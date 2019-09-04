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
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetActiveWindow () ; 
 int /*<<< orphan*/  IsChild (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
TOOLTIPS_IsWindowActive (HWND hwnd)
{
    HWND hwndActive = GetActiveWindow ();
    if (!hwndActive)
	return FALSE;
    if (hwndActive == hwnd)
	return TRUE;
    return IsChild (hwndActive, hwnd);
}