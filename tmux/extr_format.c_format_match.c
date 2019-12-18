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
struct format_modifier {int argc; char** argv; } ;
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int FNM_CASEFOLD ; 
 int REG_EXTENDED ; 
 int REG_ICASE ; 
 int REG_NOSUB ; 
 scalar_t__ fnmatch (char const*,char const*,int) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
format_match(struct format_modifier *fm, const char *pattern, const char *text)
{
	const char	*s = "";
	regex_t		 r;
	int		 flags = 0;

	if (fm->argc >= 1)
		s = fm->argv[0];
	if (strchr(s, 'r') == NULL) {
		if (strchr(s, 'i') != NULL)
			flags |= FNM_CASEFOLD;
		if (fnmatch(pattern, text, flags) != 0)
			return (xstrdup("0"));
	} else {
		flags = REG_EXTENDED|REG_NOSUB;
		if (strchr(s, 'i') != NULL)
			flags |= REG_ICASE;
		if (regcomp(&r, pattern, flags) != 0)
			return (xstrdup("0"));
		if (regexec(&r, text, 0, NULL, 0) != 0) {
			regfree(&r);
			return (xstrdup("0"));
		}
		regfree(&r);
	}
	return (xstrdup("1"));
}