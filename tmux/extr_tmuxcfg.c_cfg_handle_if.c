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
struct cfg_cond {size_t line; int skip; scalar_t__ saw_else; scalar_t__ met; } ;

/* Variables and functions */
 struct cfg_cond* TAILQ_FIRST (struct cfg_conds*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (struct cfg_conds*,struct cfg_cond*,int /*<<< orphan*/ ) ; 
 scalar_t__ cfg_check_cond (char const*,size_t,char const*,int*,struct client*,struct cmd_find_state*) ; 
 int /*<<< orphan*/  entry ; 
 struct cfg_cond* xcalloc (int,int) ; 

__attribute__((used)) static void
cfg_handle_if(const char *path, size_t line, struct cfg_conds *conds,
    const char *p, struct client *c, struct cmd_find_state *fs)
{
	struct cfg_cond	*cond;
	struct cfg_cond	*parent = TAILQ_FIRST(conds);

	/*
	 * Add a new condition. If a previous condition exists and isn't
	 * currently met, this new one also can't be met.
	 */
	cond = xcalloc(1, sizeof *cond);
	cond->line = line;
	if (parent == NULL || parent->met)
		cond->met = cfg_check_cond(path, line, p, &cond->skip, c, fs);
	else
		cond->skip = 1;
	cond->saw_else = 0;
	TAILQ_INSERT_HEAD(conds, cond, entry);
}