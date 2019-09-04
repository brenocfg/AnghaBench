#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_15__ {int your_event_mask; } ;
typedef  TYPE_2__ XWindowAttributes ;
struct TYPE_16__ {scalar_t__ property; scalar_t__ selection; scalar_t__ target; int /*<<< orphan*/  time; } ;
typedef  TYPE_3__ XSelectionEvent ;
typedef  scalar_t__ Window ;
typedef  void* Time ;
struct TYPE_14__ {scalar_t__ timestamp_atom; scalar_t__ primary_atom; scalar_t__ targets_atom; scalar_t__ clipboard_atom; scalar_t__ incr_atom; scalar_t__ incr_target; int waiting_for_INCR; scalar_t__ format_string_atom; scalar_t__ rdesktop_clipboard_formats_atom; void* rdesktop_is_selection_owner; void* probing_selections; scalar_t__ auto_mode; int /*<<< orphan*/  rdesktop_clipboard_target_atom; scalar_t__ reprobe_selections; void* clipboard_timestamp; void* primary_timestamp; int /*<<< orphan*/  rdesktop_clipboard_timestamp_target_atom; int /*<<< orphan*/  rdesktop_primary_timestamp_target_atom; } ;
struct TYPE_17__ {TYPE_1__ xclip; int /*<<< orphan*/  display; int /*<<< orphan*/  wnd; } ;
typedef  TYPE_4__ RDPCLIENT ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 int /*<<< orphan*/  AnyPropertyType ; 
 int /*<<< orphan*/  DEBUG_CLIPBOARD (char*) ; 
 void* False ; 
 scalar_t__ None ; 
 int PropertyChangeMask ; 
 int /*<<< orphan*/  RDP_CF_TEXT ; 
 int Success ; 
 void* True ; 
 int /*<<< orphan*/  XConvertSelection (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDeleteProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XGetAtomName (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ XGetSelectionOwner (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XGetWindowAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int XGetWindowProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,scalar_t__*,int*,unsigned long*,unsigned long*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  XMaxRequestSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSelectInput (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cliprdr_send_native_format_announce (TYPE_4__*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  cliprdr_send_simple_native_format_announce (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  helper_cliprdr_send_empty_response (TYPE_4__*) ; 
 int /*<<< orphan*/  xclip_clear_target_props (TYPE_4__*) ; 
 int /*<<< orphan*/  xclip_probe_selections (TYPE_4__*) ; 
 int /*<<< orphan*/  xclip_send_data_with_convert (TYPE_4__*,int /*<<< orphan*/ *,unsigned long,scalar_t__) ; 

void
xclip_handle_SelectionNotify(RDPCLIENT * This, XSelectionEvent * event)
{
	unsigned long nitems, bytes_left;
	XWindowAttributes wa;
	Atom type;
	Atom *supported_targets;
	int res, i, format;
	uint8 *data = NULL;

	if (event->property == None)
		goto fail;

	DEBUG_CLIPBOARD(("xclip_handle_SelectionNotify: selection=%s, target=%s, property=%s\n",
			 XGetAtomName(This->display, event->selection),
			 XGetAtomName(This->display, event->target),
			 XGetAtomName(This->display, event->property)));

	if (event->target == This->xclip.timestamp_atom)
	{
		if (event->selection == This->xclip.primary_atom)
		{
			res = XGetWindowProperty(This->display, This->wnd,
						 This->xclip.rdesktop_primary_timestamp_target_atom, 0,
						 XMaxRequestSize(This->display), False, AnyPropertyType,
						 &type, &format, &nitems, &bytes_left, &data);
		}
		else
		{
			res = XGetWindowProperty(This->display, This->wnd,
						 This->xclip.rdesktop_clipboard_timestamp_target_atom, 0,
						 XMaxRequestSize(This->display), False, AnyPropertyType,
						 &type, &format, &nitems, &bytes_left, &data);
		}


		if ((res != Success) || (nitems != 1) || (format != 32))
		{
			DEBUG_CLIPBOARD(("XGetWindowProperty failed!\n"));
			goto fail;
		}

		if (event->selection == This->xclip.primary_atom)
		{
			This->xclip.primary_timestamp = *(Time *) data;
			if (This->xclip.primary_timestamp == 0)
				This->xclip.primary_timestamp++;
			XDeleteProperty(This->display, This->wnd, This->xclip.rdesktop_primary_timestamp_target_atom);
			DEBUG_CLIPBOARD(("Got PRIMARY timestamp: %u\n",
					 (unsigned) This->xclip.primary_timestamp));
		}
		else
		{
			This->xclip.clipboard_timestamp = *(Time *) data;
			if (This->xclip.clipboard_timestamp == 0)
				This->xclip.clipboard_timestamp++;
			XDeleteProperty(This->display, This->wnd, This->xclip.rdesktop_clipboard_timestamp_target_atom);
			DEBUG_CLIPBOARD(("Got CLIPBOARD timestamp: %u\n",
					 (unsigned) This->xclip.clipboard_timestamp));
		}

		XFree(data);

		if (This->xclip.primary_timestamp && This->xclip.clipboard_timestamp)
		{
			if (This->xclip.primary_timestamp > This->xclip.clipboard_timestamp)
			{
				DEBUG_CLIPBOARD(("PRIMARY is most recent selection.\n"));
				XConvertSelection(This->display, This->xclip.primary_atom, This->xclip.targets_atom,
						  This->xclip.rdesktop_clipboard_target_atom, This->wnd,
						  event->time);
			}
			else
			{
				DEBUG_CLIPBOARD(("CLIPBOARD is most recent selection.\n"));
				XConvertSelection(This->display, This->xclip.clipboard_atom, This->xclip.targets_atom,
						  This->xclip.rdesktop_clipboard_target_atom, This->wnd,
						  event->time);
			}
		}

		return;
	}

	if (This->xclip.probing_selections && This->xclip.reprobe_selections)
	{
		This->xclip.probing_selections = False;
		xclip_probe_selections(This);
		return;
	}

	res = XGetWindowProperty(This->display, This->wnd, This->xclip.rdesktop_clipboard_target_atom,
				 0, XMaxRequestSize(This->display), False, AnyPropertyType,
				 &type, &format, &nitems, &bytes_left, &data);

	xclip_clear_target_props(This);

	if (res != Success)
	{
		DEBUG_CLIPBOARD(("XGetWindowProperty failed!\n"));
		goto fail;
	}

	if (type == This->xclip.incr_atom)
	{
		DEBUG_CLIPBOARD(("Received INCR.\n"));

		XGetWindowAttributes(This->display, This->wnd, &wa);
		if ((wa.your_event_mask | PropertyChangeMask) != wa.your_event_mask)
		{
			XSelectInput(This->display, This->wnd, (wa.your_event_mask | PropertyChangeMask));
		}
		XFree(data);
		This->xclip.incr_target = event->target;
		This->xclip.waiting_for_INCR = 1;
		goto end;
	}

	/* Negotiate target format */
	if (event->target == This->xclip.targets_atom)
	{
		/* Determine the best of text This->xclip.targets that we have available:
		   Prefer UTF8_STRING > text/unicode (unspecified encoding) > STRING
		   (ignore TEXT and COMPOUND_TEXT because we don't have code to handle them)
		 */
		int text_target_satisfaction = 0;
		Atom best_text_target = 0;	/* measures how much we're satisfied with what we found */
		if (type != None)
		{
			supported_targets = (Atom *) data;
			for (i = 0; i < nitems; i++)
			{
				DEBUG_CLIPBOARD(("Target %d: %s\n", i,
						 XGetAtomName(This->display, supported_targets[i])));
				if (supported_targets[i] == This->xclip.format_string_atom)
				{
					if (text_target_satisfaction < 1)
					{
						DEBUG_CLIPBOARD(("Other party supports STRING, choosing that as best_target\n"));
						best_text_target = supported_targets[i];
						text_target_satisfaction = 1;
					}
				}
#ifdef USE_UNICODE_CLIPBOARD
				else if (supported_targets[i] == This->xclip.format_unicode_atom)
				{
					if (text_target_satisfaction < 2)
					{
						DEBUG_CLIPBOARD(("Other party supports text/unicode, choosing that as best_target\n"));
						best_text_target = supported_targets[i];
						text_target_satisfaction = 2;
					}
				}
				else if (supported_targets[i] == This->xclip.format_utf8_string_atom)
				{
					if (text_target_satisfaction < 3)
					{
						DEBUG_CLIPBOARD(("Other party supports UTF8_STRING, choosing that as best_target\n"));
						best_text_target = supported_targets[i];
						text_target_satisfaction = 3;
					}
				}
#endif
				else if (supported_targets[i] == This->xclip.rdesktop_clipboard_formats_atom)
				{
					if (This->xclip.probing_selections && (text_target_satisfaction < 4))
					{
						DEBUG_CLIPBOARD(("Other party supports native formats, choosing that as best_target\n"));
						best_text_target = supported_targets[i];
						text_target_satisfaction = 4;
					}
				}
			}
		}

		/* Kickstarting the next step in the process of satisfying RDP's
		   clipboard request -- specifically, requesting the actual clipboard data.
		 */
		if ((best_text_target != 0)
		    && (!This->xclip.probing_selections
			|| (best_text_target == This->xclip.rdesktop_clipboard_formats_atom)))
		{
			XConvertSelection(This->display, event->selection, best_text_target,
					  This->xclip.rdesktop_clipboard_target_atom, This->wnd, event->time);
			goto end;
		}
		else
		{
			DEBUG_CLIPBOARD(("Unable to find a textual target to satisfy RDP clipboard text request\n"));
			goto fail;
		}
	}
	else
	{
		if (This->xclip.probing_selections)
		{
			Window primary_owner, clipboard_owner;

			/* FIXME:
			   Without XFIXES, we must make sure that the other
			   rdesktop owns all relevant selections or we might try
			   to get a native format from non-rdesktop window later
			   on. */

			clipboard_owner = XGetSelectionOwner(This->display, This->xclip.clipboard_atom);

			if (This->xclip.auto_mode)
				primary_owner = XGetSelectionOwner(This->display, This->xclip.primary_atom);
			else
				primary_owner = clipboard_owner;

			if (primary_owner != clipboard_owner)
				goto fail;

			DEBUG_CLIPBOARD(("Got fellow rdesktop formats\n"));
			This->xclip.probing_selections = False;
			This->xclip.rdesktop_is_selection_owner = True;
			cliprdr_send_native_format_announce(This, data, nitems);
		}
		else if (!xclip_send_data_with_convert(This, data, nitems, event->target))
		{
			goto fail;
		}
	}

      end:
	if (data)
		XFree(data);

	return;

      fail:
	xclip_clear_target_props(This);
	if (This->xclip.probing_selections)
	{
		DEBUG_CLIPBOARD(("Unable to find suitable target. Using default text format.\n"));
		This->xclip.probing_selections = False;
		This->xclip.rdesktop_is_selection_owner = False;

		/* FIXME:
		   Without XFIXES, we cannot reliably know the formats offered by an
		   upcoming selection owner, so we just lie about him offering
		   RDP_CF_TEXT. */
		cliprdr_send_simple_native_format_announce(This, RDP_CF_TEXT);
	}
	else
	{
		helper_cliprdr_send_empty_response(This);
	}
	goto end;
}