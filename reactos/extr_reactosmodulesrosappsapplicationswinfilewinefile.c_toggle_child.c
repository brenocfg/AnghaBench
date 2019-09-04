#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  hMenuOptions; } ;
struct TYPE_3__ {scalar_t__ mode; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ Globals ; 
 scalar_t__ IsWindowVisible (int /*<<< orphan*/ ) ; 
 int MF_BYCOMMAND ; 
 int MF_CHECKED ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fullscreen_move (int /*<<< orphan*/ ) ; 
 TYPE_1__ g_fullscreen ; 
 int /*<<< orphan*/  resize_frame_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void toggle_child(HWND hwnd, UINT cmd, HWND hchild)
{
	BOOL vis = IsWindowVisible(hchild);

	CheckMenuItem(Globals.hMenuOptions, cmd, vis?MF_BYCOMMAND:MF_BYCOMMAND|MF_CHECKED);

	ShowWindow(hchild, vis?SW_HIDE:SW_SHOW);

	if (g_fullscreen.mode)
		fullscreen_move(hwnd);

	resize_frame_client(hwnd);
}