#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hMainWnd; scalar_t__ hdrivebar; } ;
struct TYPE_4__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
typedef  TYPE_1__ RECT ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__ Globals ; 
 int /*<<< orphan*/  MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SIZE ; 
 int /*<<< orphan*/  create_drive_bar () ; 

__attribute__((used)) static void refresh_drives(void)
{
	RECT rect;

	/* destroy drive bar */
	DestroyWindow(Globals.hdrivebar);
	Globals.hdrivebar = 0;

	/* re-create drive bar */
	create_drive_bar();

	/* update window layout */
	GetClientRect(Globals.hMainWnd, &rect);
	SendMessageW(Globals.hMainWnd, WM_SIZE, 0, MAKELONG(rect.right, rect.bottom));
}