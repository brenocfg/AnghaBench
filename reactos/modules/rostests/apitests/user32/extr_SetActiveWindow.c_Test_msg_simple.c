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

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_CACHE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushMessages () ; 
 int /*<<< orphan*/  SetActiveWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCursorPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  activate1to2_chain ; 
 int /*<<< orphan*/  activate2to1_chain ; 
 int /*<<< orphan*/  create_test_windows () ; 
 int /*<<< orphan*/  destroy_test_window () ; 
 int /*<<< orphan*/  hWnd1 ; 
 int /*<<< orphan*/  hWnd2 ; 
 int /*<<< orphan*/  set_default_zorder () ; 

void Test_msg_simple()
{
    SetCursorPos(0,0);

    create_test_windows();
    set_default_zorder();

    SetActiveWindow(hWnd1);
    FlushMessages();
    COMPARE_CACHE(activate2to1_chain);

    SetActiveWindow(hWnd2);
    FlushMessages();
    COMPARE_CACHE(activate1to2_chain);

    destroy_test_window();
}