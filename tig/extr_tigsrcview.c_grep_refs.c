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
struct view_column {int dummy; } ;
struct view {int /*<<< orphan*/  regex; } ;
struct ref {int /*<<< orphan*/  name; struct ref* next; } ;
typedef  int /*<<< orphan*/  regmatch_t ;

/* Variables and functions */
 int /*<<< orphan*/  regexec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
grep_refs(struct view *view, struct view_column *column, const struct ref *ref)
{
	regmatch_t pmatch;

	for (; ref; ref = ref->next) {
		if (!regexec(view->regex, ref->name, 1, &pmatch, 0))
			return true;
	}

	return false;
}