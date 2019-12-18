#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_3__ {scalar_t__ rm_so; scalar_t__ rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;

/* Variables and functions */
 int /*<<< orphan*/  regsub_copy (char**,size_t*,char const*,scalar_t__,scalar_t__) ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static void
regsub_expand(char **buf, size_t *len, const char *with, const char *text,
    regmatch_t *m, u_int n)
{
	const char	*cp;
	u_int		 i;

	for (cp = with; *cp != '\0'; cp++) {
		if (*cp == '\\') {
			cp++;
			if (*cp >= '0' && *cp <= '9') {
				i = *cp - '0';
				if (i < n && m[i].rm_so != m[i].rm_eo) {
					regsub_copy(buf, len, text, m[i].rm_so,
					    m[i].rm_eo);
					continue;
				}
			}
		}
		*buf = xrealloc(*buf, (*len) + 2);
		(*buf)[(*len)++] = *cp;
	}
}