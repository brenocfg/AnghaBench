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
 scalar_t__ strchr (char const*,char) ; 
 int strspn (char*,char const*) ; 

char *argsep(char **stringp, const char *delim) {
	char *start = *stringp;
	char *end = start;
	bool in_string = false;
	bool in_char = false;
	bool escaped = false;
	while (1) {
		if (*end == '"' && !in_char && !escaped) {
			in_string = !in_string;
		} else if (*end == '\'' && !in_string && !escaped) {
			in_char = !in_char;
		} else if (*end == '\\') {
			escaped = !escaped;
		} else if (*end == '\0') {
			*stringp = NULL;
			break;
		} else if (!in_string && !in_char && !escaped && strchr(delim, *end)) {
			if (end - start) {
				*(end++) = 0;
				*stringp = end + strspn(end, delim);;
				if (!**stringp) *stringp = NULL;
				break;
			} else {
				++start;
				end = start;
			}
		}
		if (*end != '\\') {
			escaped = false;
		}
		++end;
	}
	return start;
}