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
 char* argsep_next_interesting (char*,char const*) ; 

char *argsep(char **stringp, const char *delim, char *matched) {
	char *start = *stringp;
	char *end = start;
	bool in_string = false;
	bool in_char = false;
	bool escaped = false;
	char *interesting = NULL;

	while ((interesting = argsep_next_interesting(end, delim))) {
		if (escaped && interesting != end) {
			escaped = false;
		}
		if (*interesting == '"' && !in_char && !escaped) {
			in_string = !in_string;
			end = interesting + 1;
		} else if (*interesting == '\'' && !in_string && !escaped) {
			in_char = !in_char;
			end = interesting + 1;
		} else if (*interesting == '\\') {
			escaped = !escaped;
			end = interesting + 1;
		} else if (!in_string && !in_char && !escaped) {
			// We must have matched a separator
			end = interesting;
			if (matched) {
				*matched = *end;
			}
			if (end - start) {
				*(end++) = 0;
				*stringp = end;
				break;
			} else {
				end = ++start;
			}
		} else {
			end++;
		}
	}
	if (!interesting) {
		*stringp = NULL;
		if (matched) {
			*matched = '\0';
		}
	}
	return start;
}