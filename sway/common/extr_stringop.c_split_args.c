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
 void* malloc (int) ; 
 char** realloc (char**,int) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strspn (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whitespace ; 

char **split_args(const char *start, int *argc) {
	*argc = 0;
	int alloc = 2;
	char **argv = malloc(sizeof(char *) * alloc);
	bool in_token = false;
	bool in_string = false;
	bool in_char = false;
	bool in_brackets = false; // brackets are used for critera
	bool escaped = false;
	const char *end = start;
	if (start) {
		while (*start) {
			if (!in_token) {
				start = (end += strspn(end, whitespace));
				in_token = true;
			}
			if (*end == '"' && !in_char && !escaped) {
				in_string = !in_string;
			} else if (*end == '\'' && !in_string && !escaped) {
				in_char = !in_char;
			} else if (*end == '[' && !in_string && !in_char && !in_brackets && !escaped) {
				in_brackets = true;
			} else if (*end == ']' && !in_string && !in_char && in_brackets && !escaped) {
				in_brackets = false;
			} else if (*end == '\\') {
				escaped = !escaped;
			} else if (*end == '\0' || (!in_string && !in_char && !in_brackets
						&& !escaped && strchr(whitespace, *end))) {
				goto add_token;
			}
			if (*end != '\\') {
				escaped = false;
			}
			++end;
			continue;
			add_token:
			if (end - start > 0) {
				char *token = malloc(end - start + 1);
				strncpy(token, start, end - start + 1);
				token[end - start] = '\0';
				argv[*argc] = token;
				if (++*argc + 1 == alloc) {
					argv = realloc(argv, (alloc *= 2) * sizeof(char *));
				}
			}
			in_token = false;
			escaped = false;
		}
	}
	argv[*argc] = NULL;
	return argv;
}