#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  scalar_t__ Window ;
struct TYPE_6__ {int /*<<< orphan*/  rdesktop_clipboard_target_atom; int /*<<< orphan*/  targets_atom; int /*<<< orphan*/  clipboard_atom; int /*<<< orphan*/  primary_atom; int /*<<< orphan*/  rdesktop_clipboard_timestamp_target_atom; int /*<<< orphan*/  timestamp_atom; int /*<<< orphan*/  rdesktop_primary_timestamp_target_atom; scalar_t__ clipboard_timestamp; scalar_t__ primary_timestamp; scalar_t__ auto_mode; int /*<<< orphan*/  rdesktop_native_atom; scalar_t__ rdesktop_is_selection_owner; scalar_t__ probing_selections; int /*<<< orphan*/  rdp_clipboard_request_format; } ;
struct TYPE_7__ {int /*<<< orphan*/  wnd; TYPE_1__ xclip; int /*<<< orphan*/  display; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentTime ; 
 int /*<<< orphan*/  DEBUG_CLIPBOARD (char*) ; 
 scalar_t__ None ; 
 int /*<<< orphan*/  PropModeReplace ; 
 int /*<<< orphan*/  XA_INTEGER ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  XConvertSelection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XGetSelectionOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  helper_cliprdr_send_empty_response (TYPE_2__*) ; 
 int /*<<< orphan*/  xclip_clear_target_props (TYPE_2__*) ; 

void
ui_clip_request_data(RDPCLIENT * This, uint32 format)
{
	Window primary_owner, clipboard_owner;

	DEBUG_CLIPBOARD(("Request from server for format %d\n", format));
	This->xclip.rdp_clipboard_request_format = format;

	if (This->xclip.probing_selections)
	{
		DEBUG_CLIPBOARD(("ui_clip_request_data: Selection probe in progress. Cannot handle request.\n"));
		helper_cliprdr_send_empty_response(This);
		return;
	}

	xclip_clear_target_props(This);

	if (This->xclip.rdesktop_is_selection_owner)
	{
		XChangeProperty(This->display, This->wnd, This->xclip.rdesktop_clipboard_target_atom,
				XA_INTEGER, 32, PropModeReplace, (unsigned char *) &format, 1);

		XConvertSelection(This->display, This->xclip.primary_atom, This->xclip.rdesktop_native_atom,
				  This->xclip.rdesktop_clipboard_target_atom, This->wnd, CurrentTime);
		return;
	}

	if (This->xclip.auto_mode)
		primary_owner = XGetSelectionOwner(This->display, This->xclip.primary_atom);
	else
		primary_owner = None;

	clipboard_owner = XGetSelectionOwner(This->display, This->xclip.clipboard_atom);

	/* Both available */
	if ((primary_owner != None) && (clipboard_owner != None))
	{
		This->xclip.primary_timestamp = 0;
		This->xclip.clipboard_timestamp = 0;
		XConvertSelection(This->display, This->xclip.primary_atom, This->xclip.timestamp_atom,
				  This->xclip.rdesktop_primary_timestamp_target_atom, This->wnd, CurrentTime);
		XConvertSelection(This->display, This->xclip.clipboard_atom, This->xclip.timestamp_atom,
				  This->xclip.rdesktop_clipboard_timestamp_target_atom, This->wnd, CurrentTime);
		return;
	}

	/* Just PRIMARY */
	if (primary_owner != None)
	{
		XConvertSelection(This->display, This->xclip.primary_atom, This->xclip.targets_atom,
				  This->xclip.rdesktop_clipboard_target_atom, This->wnd, CurrentTime);
		return;
	}

	/* Just CLIPBOARD */
	if (clipboard_owner != None)
	{
		XConvertSelection(This->display, This->xclip.clipboard_atom, This->xclip.targets_atom,
				  This->xclip.rdesktop_clipboard_target_atom, This->wnd, CurrentTime);
		return;
	}

	/* No data available */
	helper_cliprdr_send_empty_response(This);
}