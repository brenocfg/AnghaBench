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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int dwStyle; scalar_t__ hwndSelf; int /*<<< orphan*/  hwndNotify; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TBS_VERT ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_HSCROLL ; 
 int /*<<< orphan*/  WM_VSCROLL ; 

__attribute__((used)) static void notify_with_scroll (const TRACKBAR_INFO *infoPtr, UINT code)
{
    UINT scroll = infoPtr->dwStyle & TBS_VERT ? WM_VSCROLL : WM_HSCROLL;

    TRACE("%x\n", code);

    SendMessageW (infoPtr->hwndNotify, scroll, code, (LPARAM)infoPtr->hwndSelf);
}