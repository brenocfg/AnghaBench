#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_5__ {int /*<<< orphan*/  formats_data_length; scalar_t__ formats_data; int /*<<< orphan*/  clipboard_atom; int /*<<< orphan*/  acquire_time; int /*<<< orphan*/  primary_atom; } ;
struct TYPE_6__ {scalar_t__ wnd; TYPE_1__ xclip; int /*<<< orphan*/  display; int /*<<< orphan*/  last_gesturetime; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 scalar_t__ XGetSelectionOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetSelectionOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*) ; 
 int /*<<< orphan*/  xclip_notify_change (TYPE_2__*) ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 
 scalar_t__ xmalloc (int /*<<< orphan*/ ) ; 

void
ui_clip_format_announce(RDPCLIENT * This, uint8 * data, uint32 length)
{
	This->xclip.acquire_time = This->last_gesturetime;

	XSetSelectionOwner(This->display, This->xclip.primary_atom, This->wnd, This->xclip.acquire_time);
	if (XGetSelectionOwner(This->display, This->xclip.primary_atom) != This->wnd)
		warning("Failed to aquire ownership of PRIMARY clipboard\n");

	XSetSelectionOwner(This->display, This->xclip.clipboard_atom, This->wnd, This->xclip.acquire_time);
	if (XGetSelectionOwner(This->display, This->xclip.clipboard_atom) != This->wnd)
		warning("Failed to aquire ownership of CLIPBOARD clipboard\n");

	if (This->xclip.formats_data)
		xfree(This->xclip.formats_data);
	This->xclip.formats_data = xmalloc(length);
	memcpy(This->xclip.formats_data, data, length);
	This->xclip.formats_data_length = length;

	xclip_notify_change(This);
}