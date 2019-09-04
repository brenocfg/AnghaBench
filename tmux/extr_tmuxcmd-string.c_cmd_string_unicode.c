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
typedef  scalar_t__ wchar_t ;
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int sscanf (char const*,char*,scalar_t__*) ; 

__attribute__((used)) static int
cmd_string_unicode(wchar_t *wc, const char *s, size_t *p, char ch)
{
	int	size = (ch == 'u') ? 4 : 8;
	u_int	tmp;

	if (size == 4 && sscanf(s + *p, "%4x", &tmp) != 1)
		return (-1);
	if (size == 8 && sscanf(s + *p, "%8x", &tmp) != 1)
		return (-1);
	*p += size;

	*wc = (wchar_t)tmp;
	return (0);
}