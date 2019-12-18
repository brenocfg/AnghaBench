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
struct TYPE_4__ {int /*<<< orphan*/  rdesktop_clipboard_timestamp_target_atom; int /*<<< orphan*/  rdesktop_primary_timestamp_target_atom; int /*<<< orphan*/  rdesktop_clipboard_target_atom; } ;
struct TYPE_5__ {TYPE_1__ xclip; int /*<<< orphan*/  wnd; int /*<<< orphan*/  display; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  XDeleteProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xclip_clear_target_props(RDPCLIENT * This)
{
	XDeleteProperty(This->display, This->wnd, This->xclip.rdesktop_clipboard_target_atom);
	XDeleteProperty(This->display, This->wnd, This->xclip.rdesktop_primary_timestamp_target_atom);
	XDeleteProperty(This->display, This->wnd, This->xclip.rdesktop_clipboard_timestamp_target_atom);
}