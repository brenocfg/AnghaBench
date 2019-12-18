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
 void* FALSE ; 
 scalar_t__ compl_cont_status ; 
 void* compl_enter_selects ; 
 int /*<<< orphan*/ * compl_leader ; 
 scalar_t__ compl_matches ; 
 int /*<<< orphan*/ * compl_orig_text ; 
 int /*<<< orphan*/ * compl_pattern ; 
 void* compl_started ; 
 int /*<<< orphan*/ * edit_submode_extra ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ins_compl_clear()
{
    compl_cont_status = 0;
    compl_started = FALSE;
    compl_matches = 0;
    vim_free(compl_pattern);
    compl_pattern = NULL;
    vim_free(compl_leader);
    compl_leader = NULL;
    edit_submode_extra = NULL;
    vim_free(compl_orig_text);
    compl_orig_text = NULL;
    compl_enter_selects = FALSE;
}