#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;
struct TYPE_10__ {scalar_t__ target; } ;
struct TYPE_8__ {scalar_t__ format_string_atom; scalar_t__ rdesktop_native_atom; void* has_selection_request; TYPE_4__ selection_request; } ;
struct TYPE_9__ {TYPE_1__ xclip; int /*<<< orphan*/  display; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CLIPBOARD (char*) ; 
 void* False ; 
 scalar_t__ XA_STRING ; 
 int /*<<< orphan*/  XGetAtomName (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  crlf2lf (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  xclip_provide_selection (TYPE_2__*,TYPE_4__*,scalar_t__,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xclip_refuse_selection (TYPE_2__*,TYPE_4__*) ; 

void
ui_clip_handle_data(RDPCLIENT * This, uint8 * data, uint32 length)
{
	BOOL free_data = False;

	if (length == 0)
	{
		xclip_refuse_selection(This, &This->xclip.selection_request);
		This->xclip.has_selection_request = False;
		return;
	}

	if (This->xclip.selection_request.target == This->xclip.format_string_atom || This->xclip.selection_request.target == XA_STRING)
	{
		/* We're expecting a CF_TEXT response */
		uint8 *firstnull;

		/* translate linebreaks */
		crlf2lf(data, &length);

		/* Only send data up to null byte, if any */
		firstnull = (uint8 *) strchr((char *) data, '\0');
		if (firstnull)
		{
			length = firstnull - data + 1;
		}
	}
#ifdef USE_UNICODE_CLIPBOARD
	else if (This->xclip.selection_request.target == This->xclip.format_utf8_string_atom)
	{
		/* We're expecting a CF_UNICODETEXT response */
		iconv_t cd = iconv_open("UTF-8", WINDOWS_CODEPAGE);
		if (cd != (iconv_t) - 1)
		{
			size_t utf8_length = length * 2;
			char *utf8_data = malloc(utf8_length);
			size_t utf8_length_remaining = utf8_length;
			char *utf8_data_remaining = utf8_data;
			char *data_remaining = (char *) data;
			size_t length_remaining = (size_t) length;
			if (utf8_data == NULL)
			{
				iconv_close(cd);
				return;
			}
			iconv(cd, (ICONV_CONST char **) &data_remaining, &length_remaining,
			      &utf8_data_remaining, &utf8_length_remaining);
			iconv_close(cd);
			free_data = True;
			data = (uint8 *) utf8_data;
			length = utf8_length - utf8_length_remaining;
		}
	}
	else if (This->xclip.selection_request.target == This->xclip.format_unicode_atom)
	{
		/* We're expecting a CF_UNICODETEXT response, so what we're
		   receiving matches our requirements and there's no need
		   for further conversions. */
	}
#endif
	else if (This->xclip.selection_request.target == This->xclip.rdesktop_native_atom)
	{
		/* Pass as-is */
	}
	else
	{
		DEBUG_CLIPBOARD(("ui_clip_handle_data: BUG! I don't know how to convert selection target %s!\n", XGetAtomName(This->display, This->xclip.selection_request.target)));
		xclip_refuse_selection(This, &This->xclip.selection_request);
		This->xclip.has_selection_request = False;
		return;
	}

	xclip_provide_selection(This, &This->xclip.selection_request, This->xclip.selection_request.target, 8, data, length - 1);
	This->xclip.has_selection_request = False;

	if (free_data)
		free(data);
}