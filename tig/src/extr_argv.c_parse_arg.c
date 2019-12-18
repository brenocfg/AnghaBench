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
 scalar_t__ isspace (int) ; 

__attribute__((used)) static char *
parse_arg(char **cmd, bool remove_quotes)
{
	int quote = 0;
	char *arg = *cmd;
	char *next, *pos;

	for (pos = next = arg; *pos; pos++) {
		int c = *pos;

		if (c == '"' || c == '\'') {
			if (quote == c) {
				quote = 0;
				if (remove_quotes) {
					if (pos == arg) {
						arg++;
						next++;
					}
					continue;
				}

			} else if (!quote) {
				quote = c;
				if (remove_quotes) {
					if (pos == arg) {
						arg++;
						next++;
					}
					continue;
				}
			}

		} else if (quote && c == '\\') {
			if (remove_quotes) {
				if (pos == arg) {
					arg++;
					next++;
				}
			} else {
				*next++ = *pos;
			}
			pos++;
			if (!*pos)
				break;
		}

		if (!quote && isspace(c))
			break;

		*next++ = *pos;
	}

	if (*pos)
		*cmd = pos + 1;
	else
		*cmd = pos;
	*next = 0;
	return (!remove_quotes || !quote) ? arg : NULL;
}