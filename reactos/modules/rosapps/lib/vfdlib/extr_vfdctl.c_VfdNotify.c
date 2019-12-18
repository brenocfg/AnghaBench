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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  LPARAM ;

/* Variables and functions */
 int /*<<< orphan*/  HWND_BROADCAST ; 
 int /*<<< orphan*/  PostMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_nNotifyMsg ; 

__attribute__((used)) static __inline void VfdNotify(
	WPARAM			wParam,
	LPARAM			lParam)
{
	//	SendNotifyMessage causes volume locking conflict (I think)
	//	on Windows XP while closing an image with VfdWin
//	SendNotifyMessage(HWND_BROADCAST, uVfdMsg, wParam, lParam);
	PostMessage(HWND_BROADCAST, g_nNotifyMsg, wParam, lParam);
}