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
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CLIPBOARD (char*) ; 
 int /*<<< orphan*/  xclip_notify_change (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xclip_probe_selections (int /*<<< orphan*/ *) ; 

void
xclip_handle_SelectionClear(RDPCLIENT * This)
{
	DEBUG_CLIPBOARD(("xclip_handle_SelectionClear\n"));
	xclip_notify_change(This);
	xclip_probe_selections(This);
}