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
struct rev_flags {size_t search_offset; int with_graph; int with_reflog; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const**) ; 
 scalar_t__ argv_find_rev_flag (char const**,int /*<<< orphan*/ ,char const*,size_t,size_t*,int*,int*) ; 
 size_t strlen (char const*) ; 

bool
argv_parse_rev_flag(const char *arg, struct rev_flags *rev_flags)
{
	static const char *with_graph[] = {
		"--after=",
		"--all",
		"--all-match",
		"--ancestry-path",
		"--author-date-order",
		"--basic-regexp",
		"--before=",
		"--boundary",
		"--branches",
		"--branches=",
		"--cherry",
		"--cherry-mark",
		"--cherry-pick",
		"--committer=",
		"--date-order",
		"--dense",
		"--exclude=",
		"--extended-regexp",
		"--first-parent",
		"--fixed-strings",
		"--full-history",
		"--graph",
		"--glob=",
		"--left-only",
		"--max-parents=",
		"--max-age=",
		"--merge",
		"--merges",
		"--min-parents=",
		"--no-max-parents",
		"--no-min-parents",
		"--no-walk",
		"--perl-regexp",
		"--pickaxe-all",
		"--pickaxe-regex",
		"--regexp-ignore-case",
		"--remotes",
		"--remotes=",
		"--remove-empty",
		"--reverse",
		"--right-only",
		"--simplify-by-decoration",
		"--simplify-merges",
		"--since=",
		"--skip=",
		"--sparse",
		"--stdin",
		"--tags",
		"--tags=",
		"--topo-order",
		"--until=",
		"-E",
		"-F",
		"-i",
	};
	static const char *no_graph[] = {
		"--no-merges",
		"--follow",
		"--author=",
	};
	static const char *with_reflog[] = {
		"--walk-reflogs",
		"-g",
	};
	static const char *search_no_graph[] = {
		"--grep-reflog=",
		"--grep=",
		"-G",
		"-S",
	};
	size_t arglen = strlen(arg);
	bool graph = true;
	bool reflog = false;
	size_t search = 0;

	if (argv_find_rev_flag(with_graph, ARRAY_SIZE(with_graph), arg, arglen, NULL, NULL, NULL) ||
	    argv_find_rev_flag(no_graph, ARRAY_SIZE(no_graph), arg, arglen, NULL, &graph, NULL) ||
	    argv_find_rev_flag(with_reflog, ARRAY_SIZE(with_reflog), arg, arglen, NULL, NULL, &reflog) ||
	    argv_find_rev_flag(search_no_graph, ARRAY_SIZE(search_no_graph), arg, arglen, &search, &graph, NULL)) {
		if (rev_flags) {
			rev_flags->search_offset = search ? search : arglen;
			rev_flags->with_graph = graph;
			rev_flags->with_reflog = reflog;
		}
		return true;
	}

	return false;
}