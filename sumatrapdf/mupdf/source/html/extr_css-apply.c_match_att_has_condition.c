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
typedef  int /*<<< orphan*/  fz_xml ;

/* Variables and functions */
 char* fz_xml_att (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 size_t strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

__attribute__((used)) static int
match_att_has_condition(fz_xml *node, const char *att, const char *needle)
{
	const char *haystack = fz_xml_att(node, att);
	const char *ss;
	size_t n;
	if (haystack) {
		/* Try matching whole property first. */
		if (!strcmp(haystack, needle))
			return 1;

		/* Look for matching words. */
		n = strlen(needle);
		ss = strstr(haystack, needle);
		if (ss && (ss[n] == ' ' || ss[n] == 0) && (ss == haystack || ss[-1] == ' '))
			return 1;
	}
	return 0;
}