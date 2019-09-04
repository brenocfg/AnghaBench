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
typedef  size_t uint32 ;
struct TYPE_5__ {scalar_t__ format_string_atom; scalar_t__ rdp_clipboard_request_format; scalar_t__ rdesktop_native_atom; } ;
struct TYPE_6__ {TYPE_1__ xclip; int /*<<< orphan*/  display; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  Bool ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CLIPBOARD (char*) ; 
 int /*<<< orphan*/  False ; 
 scalar_t__ RDP_CF_TEXT ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XGetAtomName (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  helper_cliprdr_send_response (TYPE_2__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * lf2crlf (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Bool
xclip_send_data_with_convert(RDPCLIENT * This, uint8 * source, size_t source_size, Atom target)
{
	DEBUG_CLIPBOARD(("xclip_send_data_with_convert: target=%s, size=%u\n",
			 XGetAtomName(This->display, target), (unsigned) source_size));

#ifdef USE_UNICODE_CLIPBOARD
	if (target == This->xclip.format_string_atom ||
	    target == This->xclip.format_unicode_atom || target == This->xclip.format_utf8_string_atom)
	{
		size_t unicode_buffer_size;
		char *unicode_buffer;
		iconv_t cd;
		size_t unicode_buffer_size_remaining;
		char *unicode_buffer_remaining;
		char *data_remaining;
		size_t data_size_remaining;
		uint32 translated_data_size;
		uint8 *translated_data;

		if (This->xclip.rdp_clipboard_request_format != RDP_CF_TEXT)
			return False;

		/* Make an attempt to convert any string we send to Unicode.
		   We don't know what the RDP server's ANSI Codepage is, or how to convert
		   to it, so using CF_TEXT is not safe (and is unnecessary, since all
		   WinNT versions are Unicode-minded).
		 */
		if (target == This->xclip.format_string_atom)
		{
			char *locale_charset = nl_langinfo(CODESET);
			cd = iconv_open(WINDOWS_CODEPAGE, locale_charset);
			if (cd == (iconv_t) - 1)
			{
				DEBUG_CLIPBOARD(("Locale charset %s not found in iconv. Unable to convert clipboard text.\n", locale_charset));
				return False;
			}
			unicode_buffer_size = source_size * 4;
		}
		else if (target == This->xclip.format_unicode_atom)
		{
			cd = iconv_open(WINDOWS_CODEPAGE, "UCS-2");
			if (cd == (iconv_t) - 1)
			{
				return False;
			}
			unicode_buffer_size = source_size;
		}
		else if (target == This->xclip.format_utf8_string_atom)
		{
			cd = iconv_open(WINDOWS_CODEPAGE, "UTF-8");
			if (cd == (iconv_t) - 1)
			{
				return False;
			}
			/* UTF-8 is guaranteed to be less or equally compact
			   as UTF-16 for all Unicode chars >=2 bytes.
			 */
			unicode_buffer_size = source_size * 2;
		}
		else
		{
			return False;
		}

		unicode_buffer = xmalloc(unicode_buffer_size);
		unicode_buffer_size_remaining = unicode_buffer_size;
		unicode_buffer_remaining = unicode_buffer;
		data_remaining = (char *) source;
		data_size_remaining = source_size;
		iconv(cd, (ICONV_CONST char **) &data_remaining, &data_size_remaining,
		      &unicode_buffer_remaining, &unicode_buffer_size_remaining);
		iconv_close(cd);

		/* translate linebreaks */
		translated_data_size = unicode_buffer_size - unicode_buffer_size_remaining;
		translated_data = utf16_lf2crlf((uint8 *) unicode_buffer, &translated_data_size);
		if (translated_data != NULL)
		{
			DEBUG_CLIPBOARD(("Sending Unicode string of %d bytes\n",
					 translated_data_size));
			helper_cliprdr_send_response(This, translated_data, translated_data_size);
			xfree(translated_data);	/* Not the same thing as XFree! */
		}

		xfree(unicode_buffer);

		return True;
	}
#else
	if (target == This->xclip.format_string_atom)
	{
		uint8 *translated_data;
		uint32 length = source_size;

		if (This->xclip.rdp_clipboard_request_format != RDP_CF_TEXT)
			return False;

		DEBUG_CLIPBOARD(("Translating linebreaks before sending data\n"));
		translated_data = lf2crlf(source, &length);
		if (translated_data != NULL)
		{
			helper_cliprdr_send_response(This, translated_data, length);
			xfree(translated_data);	/* Not the same thing as XFree! */
		}

		return True;
	}
#endif
	else if (target == This->xclip.rdesktop_native_atom)
	{
		helper_cliprdr_send_response(This, source, source_size + 1);

		return True;
	}
	else
	{
		return False;
	}
}