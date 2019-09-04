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
struct blame {TYPE_1__* commit; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  report (char*) ; 
 scalar_t__ string_rev_is_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
check_blame_commit(struct blame *blame, bool check_null_id)
{
	if (!blame->commit)
		report("Commit data not loaded yet");
	else if (check_null_id && string_rev_is_null(blame->commit->id))
		report("No commit exist for the selected line");
	else
		return true;
	return false;
}