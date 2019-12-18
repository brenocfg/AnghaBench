#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_5__ {scalar_t__ rm_so; scalar_t__ rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  REG_STARTEND ; 
 int /*<<< orphan*/  nitems (TYPE_1__*) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regsub_copy (char**,scalar_t__*,char const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  regsub_expand (char**,scalar_t__*,char const*,char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 char* xstrdup (char*) ; 

char *
regsub(const char *pattern, const char *with, const char *text, int flags)
{
	regex_t		 r;
	regmatch_t	 m[10];
	ssize_t		 start, end, last, len = 0;
	int		 empty = 0;
	char		*buf = NULL;

	if (*text == '\0')
		return (xstrdup(""));
	if (regcomp(&r, pattern, flags) != 0)
		return (NULL);

	start = 0;
	last = 0;
	end = strlen(text);

	while (start <= end) {
		m[0].rm_so = start;
		m[0].rm_eo = end;

		if (regexec(&r, text, nitems(m), m, REG_STARTEND) != 0) {
			regsub_copy(&buf, &len, text, start, end);
			break;
		}

		/*
		 * Append any text not part of this match (from the end of the
		 * last match).
		 */
		regsub_copy(&buf, &len, text, last, m[0].rm_so);

		/*
		 * If the last match was empty and this one isn't (it is either
		 * later or has matched text), expand this match. If it is
		 * empty, move on one character and try again from there.
		 */
		if (empty || m[0].rm_so != last || m[0].rm_so != m[0].rm_eo) {
			regsub_expand(&buf, &len, with, text, m, nitems(m));

			last = m[0].rm_eo;
			start = m[0].rm_eo;
			empty = 0;
		} else {
			last = m[0].rm_eo;
			start = m[0].rm_eo + 1;
			empty = 1;
		}
	}
	buf[len] = '\0';

	regfree(&r);
	return (buf);
}