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
typedef  int /*<<< orphan*/  TASKBAR_PROGRESS_FLAGS ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  ITaskbarList3_SetProgressState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hMainDialog ; 
 int /*<<< orphan*/ * ptbl ; 

BOOL SetTaskbarProgressState(TASKBAR_PROGRESS_FLAGS tbpFlags)
{
	if (ptbl == NULL)
		return FALSE;
	return !FAILED(ITaskbarList3_SetProgressState(ptbl, hMainDialog, tbpFlags));
}