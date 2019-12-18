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
 int /*<<< orphan*/  VV_TERMRESPONSE ; 
 scalar_t__ autocmd_blocked ; 
 int /*<<< orphan*/  get_vim_var_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_termresponse ; 

void
block_autocmds()
{
# ifdef FEAT_EVAL
    /* Remember the value of v:termresponse. */
    if (autocmd_blocked == 0)
	old_termresponse = get_vim_var_str(VV_TERMRESPONSE);
# endif
    ++autocmd_blocked;
}