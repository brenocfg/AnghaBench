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
typedef  int /*<<< orphan*/  wchar_t ;
struct utf8_data {int size; int /*<<< orphan*/  width; int /*<<< orphan*/  data; } ;
typedef  enum utf8_state { ____Placeholder_utf8_state } utf8_state ;

/* Variables and functions */
 int MB_LEN_MAX ; 
 int UTF8_DONE ; 
 int UTF8_ERROR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  utf8_width (int /*<<< orphan*/ ) ; 
 int utf8proc_wctomb (char*,int /*<<< orphan*/ ) ; 
 int wctomb (char*,int /*<<< orphan*/ ) ; 

enum utf8_state
utf8_split(wchar_t wc, struct utf8_data *ud)
{
	char	s[MB_LEN_MAX];
	int	slen;

#ifdef HAVE_UTF8PROC
	slen = utf8proc_wctomb(s, wc);
#else
	slen = wctomb(s, wc);
#endif
	if (slen <= 0 || slen > (int)sizeof ud->data)
		return (UTF8_ERROR);

	memcpy(ud->data, s, slen);
	ud->size = slen;

	ud->width = utf8_width(wc);
	return (UTF8_DONE);
}