#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * we_wordv; } ;
typedef  TYPE_1__ wordexp_t ;

/* Variables and functions */
 int SIZEOF_STR ; 
 int /*<<< orphan*/  WRDE_NOCMD ; 
 char* getenv (char*) ; 
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/  string_format (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  string_ncopy_do (char*,size_t,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_nformat (char*,size_t,int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ wordexp (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wordfree (TYPE_1__*) ; 

bool
path_expand(char *dst, size_t dstlen, const char *src)
{
	if (!src)
		return false;

	if (src[0] == '~') {
		/* constrain wordexp to tilde expansion only */
		const char *ifs = getenv("IFS") ? getenv("IFS") : " \t\n";
		wordexp_t we_result;
		size_t metachar_pos;
		char metachars[SIZEOF_STR];
		char leading[SIZEOF_STR];

		string_format(metachars, "%s%s", "/$|&;<>(){}`", ifs);
		metachar_pos = strcspn(src, metachars);
		if (src[metachar_pos] == '/' || src[metachar_pos] == 0) {
			string_nformat(leading, metachar_pos + 1, NULL, "%s", src);
			if (wordexp(leading, &we_result, WRDE_NOCMD))
				return false;
			string_nformat(dst, dstlen, NULL, "%s%s", we_result.we_wordv[0], src + metachar_pos);
			wordfree(&we_result);
			return true;
		}
	}

	/* else */
	string_ncopy_do(dst, dstlen, src, strlen(src));
	return true;
}