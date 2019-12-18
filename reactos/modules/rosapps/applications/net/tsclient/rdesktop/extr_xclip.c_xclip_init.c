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
struct TYPE_5__ {scalar_t__ num_targets; void** targets; void* format_string_atom; void* format_unicode_atom; void* format_utf8_string_atom; void* rdesktop_clipboard_formats_atom; void* rdesktop_native_atom; void* timestamp_atom; void* targets_atom; void* rdesktop_clipboard_owner_atom; void* rdesktop_primary_owner_atom; int /*<<< orphan*/  probing_selections; void* rdesktop_selection_notify_atom; void* incr_atom; void* rdesktop_clipboard_timestamp_target_atom; void* rdesktop_primary_timestamp_target_atom; void* rdesktop_clipboard_target_atom; void* clipboard_atom; void* primary_atom; } ;
struct TYPE_6__ {TYPE_1__ xclip; int /*<<< orphan*/  display; int /*<<< orphan*/  rdpclip; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultRootWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  PropertyChangeMask ; 
 void* XA_STRING ; 
 void* XInternAtom (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSelectInput (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cliprdr_init (TYPE_2__*) ; 

void
xclip_init(RDPCLIENT * This)
{
	if (!This->rdpclip)
		return;

	if (!cliprdr_init(This))
		return;

	This->xclip.primary_atom = XInternAtom(This->display, "PRIMARY", False);
	This->xclip.clipboard_atom = XInternAtom(This->display, "CLIPBOARD", False);
	This->xclip.targets_atom = XInternAtom(This->display, "TARGETS", False);
	This->xclip.timestamp_atom = XInternAtom(This->display, "TIMESTAMP", False);
	This->xclip.rdesktop_clipboard_target_atom =
		XInternAtom(This->display, "_RDESKTOP_CLIPBOARD_TARGET", False);
	This->xclip.rdesktop_primary_timestamp_target_atom =
		XInternAtom(This->display, "_RDESKTOP_PRIMARY_TIMESTAMP_TARGET", False);
	This->xclip.rdesktop_clipboard_timestamp_target_atom =
		XInternAtom(This->display, "_RDESKTOP_CLIPBOARD_TIMESTAMP_TARGET", False);
	This->xclip.incr_atom = XInternAtom(This->display, "INCR", False);
	This->xclip.format_string_atom = XInternAtom(This->display, "STRING", False);
	This->xclip.format_utf8_string_atom = XInternAtom(This->display, "UTF8_STRING", False);
	This->xclip.format_unicode_atom = XInternAtom(This->display, "text/unicode", False);

	/* rdesktop sets _RDESKTOP_SELECTION_NOTIFY on the root window when acquiring the clipboard.
	   Other interested rdesktops can use this to notify their server of the available formats. */
	This->xclip.rdesktop_selection_notify_atom =
		XInternAtom(This->display, "_RDESKTOP_SELECTION_NOTIFY", False);
	XSelectInput(This->display, DefaultRootWindow(This->display), PropertyChangeMask);
	This->xclip.probing_selections = False;

	This->xclip.rdesktop_native_atom = XInternAtom(This->display, "_RDESKTOP_NATIVE", False);
	This->xclip.rdesktop_clipboard_formats_atom =
		XInternAtom(This->display, "_RDESKTOP_CLIPBOARD_FORMATS", False);
	This->xclip.rdesktop_primary_owner_atom = XInternAtom(This->display, "_RDESKTOP_PRIMARY_OWNER", False);
	This->xclip.rdesktop_clipboard_owner_atom = XInternAtom(This->display, "_RDESKTOP_CLIPBOARD_OWNER", False);

	This->xclip.num_targets = 0;
	This->xclip.targets[This->xclip.num_targets++] = This->xclip.targets_atom;
	This->xclip.targets[This->xclip.num_targets++] = This->xclip.timestamp_atom;
	This->xclip.targets[This->xclip.num_targets++] = This->xclip.rdesktop_native_atom;
	This->xclip.targets[This->xclip.num_targets++] = This->xclip.rdesktop_clipboard_formats_atom;
#ifdef USE_UNICODE_CLIPBOARD
	This->xclip.targets[This->xclip.num_targets++] = This->xclip.format_utf8_string_atom;
#endif
	This->xclip.targets[This->xclip.num_targets++] = This->xclip.format_unicode_atom;
	This->xclip.targets[This->xclip.num_targets++] = This->xclip.format_string_atom;
	This->xclip.targets[This->xclip.num_targets++] = XA_STRING;
}