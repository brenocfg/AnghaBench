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
struct cfg_conds {int dummy; } ;
struct cfg_cond {int saw_else; int met; int skip; } ;

/* Variables and functions */
 struct cfg_cond* TAILQ_FIRST (struct cfg_conds*) ; 
 int /*<<< orphan*/  cfg_add_cause (char*,char const*,size_t) ; 

__attribute__((used)) static void
cfg_handle_else(const char *path, size_t line, struct cfg_conds *conds)
{
	struct cfg_cond	*cond = TAILQ_FIRST(conds);

	/*
	 * If a previous condition exists and wasn't met and wasn't already
	 * %else, use this one instead.
	 */
	if (cond == NULL || cond->saw_else) {
		cfg_add_cause("%s:%zu: unexpected %%else", path, line);
		return;
	}
	cond->saw_else = 1;
	cond->met = !cond->skip;
	cond->skip = 1;
}