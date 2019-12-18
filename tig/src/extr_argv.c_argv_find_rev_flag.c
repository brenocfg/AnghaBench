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
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static inline bool
argv_find_rev_flag(const char *argv[], size_t argc, const char *arg, size_t arglen,
		   size_t *search_offset, bool *with_graph, bool *with_reflog)
{
	int i;

	for (i = 0; i < argc; i++) {
		const char *flag = argv[i];
		size_t flaglen = strlen(flag);

		if (flaglen > arglen || strncmp(arg, flag, flaglen))
			continue;

		if (search_offset)
			*search_offset = flaglen;
		else if (flaglen != arglen && flag[flaglen - 1] != '=')
			continue;

		if (with_graph)
			*with_graph = false;
		if (with_reflog)
			*with_reflog = true;

		return true;
	}

	return false;
}