#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct view {size_t lines; TYPE_1__* line; } ;
struct blame_commit {int /*<<< orphan*/  id; } ;
struct blame {struct blame_commit* commit; } ;
struct TYPE_2__ {struct blame* data; } ;

/* Variables and functions */
 scalar_t__ SIZEOF_REV ; 
 struct blame_commit* calloc (int,int) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

__attribute__((used)) static struct blame_commit *
get_blame_commit(struct view *view, const char *id)
{
	size_t i;

	for (i = 0; i < view->lines; i++) {
		struct blame *blame = view->line[i].data;

		if (!blame->commit)
			continue;

		if (!strncmp(blame->commit->id, id, SIZEOF_REV - 1))
			return blame->commit;
	}

	{
		struct blame_commit *commit = calloc(1, sizeof(*commit));

		if (commit)
			string_ncopy(commit->id, id, SIZEOF_REV);
		return commit;
	}
}