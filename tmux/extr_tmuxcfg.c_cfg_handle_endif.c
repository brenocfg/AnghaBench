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
struct cfg_cond {int dummy; } ;

/* Variables and functions */
 struct cfg_cond* TAILQ_FIRST (struct cfg_conds*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct cfg_conds*,struct cfg_cond*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg_add_cause (char*,char const*,size_t) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct cfg_cond*) ; 

__attribute__((used)) static void
cfg_handle_endif(const char *path, size_t line, struct cfg_conds *conds)
{
	struct cfg_cond	*cond = TAILQ_FIRST(conds);

	/*
	 * Remove previous condition if one exists.
	 */
	if (cond == NULL) {
		cfg_add_cause("%s:%zu: unexpected %%endif", path, line);
		return;
	}
	TAILQ_REMOVE(conds, cond, entry);
	free(cond);
}