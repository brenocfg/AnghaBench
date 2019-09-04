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
struct ref {int dummy; } ;
struct line {int dummy; } ;
struct commit {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 struct ref* get_ref_list (int /*<<< orphan*/ ) ; 
 scalar_t__ main_check_commit_refs (struct line const*) ; 
 int /*<<< orphan*/  main_mark_no_commit_refs (struct line const*) ; 

__attribute__((used)) static inline const struct ref *
main_get_commit_refs(const struct line *line, struct commit *commit)
{
	const struct ref *refs = NULL;

	if (main_check_commit_refs(line) && !(refs = get_ref_list(commit->id)))
		main_mark_no_commit_refs(line);

	return refs;
}