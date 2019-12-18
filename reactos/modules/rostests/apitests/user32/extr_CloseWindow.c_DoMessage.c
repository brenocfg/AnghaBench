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
typedef  scalar_t__ WPARAM ;
typedef  scalar_t__ UINT ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ WM_ACTIVATE ; 
 scalar_t__ WM_NCACTIVATE ; 
 scalar_t__ WM_SYSCOMMAND ; 
 scalar_t__ WM_TIMER ; 
 scalar_t__ WM_WINDOWPOSCHANGING ; 
 int /*<<< orphan*/  s_bTracing ; 
 int /*<<< orphan*/  s_nWM_ACTIVATE ; 
 int /*<<< orphan*/  s_nWM_NCACTIVATE ; 
 int /*<<< orphan*/  s_nWM_SYSCOMMAND ; 
 int /*<<< orphan*/  s_nWM_WINDOWPOSCHANGING ; 
 int /*<<< orphan*/  trace (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
DoMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_TIMER || !s_bTracing)
        return;

    trace("uMsg:0x%04X, wParam:0x%08lX, lParam:0x%08lX\n", uMsg, (LONG)wParam, (LONG)lParam);

    if (uMsg == WM_SYSCOMMAND)
    {
        ++s_nWM_SYSCOMMAND;
    }

    if (uMsg == WM_NCACTIVATE)
        ++s_nWM_NCACTIVATE;

    if (uMsg == WM_WINDOWPOSCHANGING)
        ++s_nWM_WINDOWPOSCHANGING;

    if (uMsg == WM_ACTIVATE)
        ++s_nWM_ACTIVATE;
}