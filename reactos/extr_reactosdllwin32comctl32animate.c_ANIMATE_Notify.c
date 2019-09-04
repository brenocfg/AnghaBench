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
struct TYPE_3__ {scalar_t__ hwndSelf; int /*<<< orphan*/  hwndNotify; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_1__ ANIMATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetDlgCtrlID (scalar_t__) ; 
 int /*<<< orphan*/  MAKEWPARAM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_COMMAND ; 

__attribute__((used)) static void ANIMATE_Notify(const ANIMATE_INFO *infoPtr, UINT notif)
{
    PostMessageW(infoPtr->hwndNotify, WM_COMMAND,
		 MAKEWPARAM(GetDlgCtrlID(infoPtr->hwndSelf), notif),
		 (LPARAM)infoPtr->hwndSelf);
}