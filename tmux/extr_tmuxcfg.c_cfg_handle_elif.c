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
struct cmd_find_state {int dummy; } ;
struct client {int dummy; } ;
struct cfg_conds {int dummy; } ;
struct cfg_cond {scalar_t__ met; int /*<<< orphan*/  skip; scalar_t__ saw_else; } ;

/* Variables and functions */
 struct cfg_cond* TAILQ_FIRST (struct cfg_conds*) ; 
 int /*<<< orphan*/  cfg_add_cause (char*,char const*,size_t) ; 
 scalar_t__ cfg_check_cond (char const*,size_t,char const*,int /*<<< orphan*/ *,struct client*,struct cmd_find_state*) ; 

__attribute__((used)) static void
cfg_handle_elif(const char *path, size_t line, struct cfg_conds *conds,
    const char *p, struct client *c, struct cmd_find_state *fs)
{
	struct cfg_cond	*cond = TAILQ_FIRST(conds);

	/*
	 * If a previous condition exists and wasn't met, check this
	 * one instead and change the state.
	 */
	if (cond == NULL || cond->saw_else)
		cfg_add_cause("%s:%zu: unexpected %%elif", path, line);
	else if (!cond->skip)
		cond->met = cfg_check_cond(path, line, p, &cond->skip, c, fs);
	else
		cond->met = 0;
}