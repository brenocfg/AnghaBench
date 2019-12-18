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
 int VIS_CSTYLE ; 
 int VIS_DQ ; 
 int VIS_NL ; 
 int VIS_OCTAL ; 
 int VIS_TAB ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * strchr (char const*,char const) ; 
 size_t strcspn (char const*,char const*) ; 
 int /*<<< orphan*/  utf8_stravis (char**,char const*,int) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,...) ; 
 char* xstrdup (char const*) ; 

char *
args_escape(const char *s)
{
	static const char	 quoted[] = " #\"';${}";
	char			*escaped, *result;
	int			 flags;

	if (*s == '\0')
		return (xstrdup(s));
	if (s[0] != ' ' &&
	    (strchr(quoted, s[0]) != NULL || s[0] == '~') &&
	    s[1] == '\0') {
		xasprintf(&escaped, "\\%c", s[0]);
		return (escaped);
	}

	flags = VIS_OCTAL|VIS_CSTYLE|VIS_TAB|VIS_NL;
	if (s[strcspn(s, quoted)] != '\0')
		flags |= VIS_DQ;
	utf8_stravis(&escaped, s, flags);

	if (flags & VIS_DQ) {
		if (*escaped == '~')
			xasprintf(&result, "\"\\%s\"", escaped);
		else
			xasprintf(&result, "\"%s\"", escaped);
	} else {
		if (*escaped == '~')
			xasprintf(&result, "\\%s", escaped);
		else
			result = xstrdup(escaped);
	}
	free(escaped);
	return (result);
}