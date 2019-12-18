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

/* Variables and functions */
 int /*<<< orphan*/  utf8proc_codepoint_valid (int /*<<< orphan*/ ) ; 
 int utf8proc_encode_char (int /*<<< orphan*/ ,char*) ; 

int
utf8proc_wctomb(char *s, wchar_t wc)
{
	if (s == NULL)
		return (0);

	if (!utf8proc_codepoint_valid(wc))
		return (-1);
	return (utf8proc_encode_char(wc, s));
}