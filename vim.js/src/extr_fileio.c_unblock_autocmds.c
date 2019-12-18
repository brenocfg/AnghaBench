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
 int /*<<< orphan*/  EVENT_TERMRESPONSE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  VV_TERMRESPONSE ; 
 int /*<<< orphan*/  apply_autocmds (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ autocmd_blocked ; 
 int /*<<< orphan*/  curbuf ; 
 scalar_t__ get_vim_var_str (int /*<<< orphan*/ ) ; 
 scalar_t__ old_termresponse ; 

void
unblock_autocmds()
{
    --autocmd_blocked;

# ifdef FEAT_EVAL
    /* When v:termresponse was set while autocommands were blocked, trigger
     * the autocommands now.  Esp. useful when executing a shell command
     * during startup (vimdiff). */
    if (autocmd_blocked == 0
		      && get_vim_var_str(VV_TERMRESPONSE) != old_termresponse)
	apply_autocmds(EVENT_TERMRESPONSE, NULL, NULL, FALSE, curbuf);
# endif
}