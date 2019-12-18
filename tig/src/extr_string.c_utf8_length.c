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

/* Variables and functions */
 char const* strchr (char const*,char) ; 
 size_t unicode_width (unsigned long,int) ; 
 unsigned char utf8_char_length (char const*) ; 
 unsigned long utf8_to_unicode (char const*,unsigned char) ; 

size_t
utf8_length(const char **start, int max_chars, size_t skip, int *width, size_t max_width, int *trimmed, bool reserve, int tab_size)
{
	const char *string = *start;
	const char *end = max_chars < 0 ? strchr(string, '\0') : string + max_chars;
	unsigned char last_bytes = 0;
	size_t last_ucwidth = 0;

	*width = 0;
	*trimmed = 0;

	while (string < end) {
		unsigned char bytes = utf8_char_length(string);
		size_t ucwidth;
		unsigned long unicode;

		if (string + bytes > end)
			break;

		/* Change representation to figure out whether
		 * it is a single- or double-width character. */

		unicode = utf8_to_unicode(string, bytes);
		/* FIXME: Graceful handling of invalid Unicode character. */
		if (!unicode)
			break;

		ucwidth = unicode_width(unicode, tab_size);
		if (skip > 0) {
			skip -= ucwidth <= skip ? ucwidth : skip;
			*start += bytes;
		}
		*width  += ucwidth;
		if (max_width > 0 && *width > max_width) {
			*trimmed = 1;
			*width -= ucwidth;
			if (reserve && *width == max_width) {
				string -= last_bytes;
				*width -= last_ucwidth;
			}
			break;
		}

		string  += bytes;
		if (ucwidth) {
			last_bytes = bytes;
			last_ucwidth = ucwidth;
		} else {
			last_bytes += bytes;
		}
	}

	return string - *start;
}