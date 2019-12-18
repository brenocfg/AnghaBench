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
 int /*<<< orphan*/ * strchr (char*,char const) ; 
 int strlen (char const*) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static char *
format_quote(const char *s)
{
	const char	*cp;
	char		*out, *at;

	at = out = xmalloc(strlen(s) * 2 + 1);
	for (cp = s; *cp != '\0'; cp++) {
		if (strchr("|&;<>()$`\\\"'*?[# =%", *cp) != NULL)
			*at++ = '\\';
		*at++ = *cp;
	}
	*at = '\0';
	return (out);
}