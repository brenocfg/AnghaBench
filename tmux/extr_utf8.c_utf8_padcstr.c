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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 scalar_t__ utf8_cstrwidth (char const*) ; 
 char* xmalloc (scalar_t__) ; 
 char* xstrdup (char const*) ; 

char *
utf8_padcstr(const char *s, u_int width)
{
	size_t	 slen;
	char	*out;
	u_int	  n, i;

	n = utf8_cstrwidth(s);
	if (n >= width)
		return (xstrdup(s));

	slen = strlen(s);
	out = xmalloc(slen + 1 + (width - n));
	memcpy(out, s, slen);
	for (i = n; i < width; i++)
		out[slen++] = ' ';
	out[slen] = '\0';
	return (out);
}