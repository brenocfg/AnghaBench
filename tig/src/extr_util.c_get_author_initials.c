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
typedef  int /*<<< orphan*/  initials ;

/* Variables and functions */
 scalar_t__ is_initial_sep (char const) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* strchr (char const*,char) ; 
 unsigned char utf8_char_length (char const*) ; 

__attribute__((used)) static const char *
get_author_initials(const char *author)
{
	static char initials[256];
	size_t pos = 0;
	const char *end = strchr(author, '\0');

#define is_initial_sep(c) (isspace(c) || ispunct(c) || (c) == '@' || (c) == '-')

	memset(initials, 0, sizeof(initials));
	while (author < end) {
		unsigned char bytes;
		size_t i;

		while (author < end && is_initial_sep(*author))
			author++;

		bytes = utf8_char_length(author);
		if (bytes >= sizeof(initials) - 1 - pos)
			break;
		while (bytes--) {
			initials[pos++] = *author++;
		}

		i = pos;
		while (author < end && !is_initial_sep(*author)) {
			bytes = utf8_char_length(author);
			if (bytes >= sizeof(initials) - 1 - i) {
				while (author < end && !is_initial_sep(*author))
					author++;
				break;
			}
			while (bytes--) {
				initials[i++] = *author++;
			}
		}

		initials[i++] = 0;
	}

	return initials;
}