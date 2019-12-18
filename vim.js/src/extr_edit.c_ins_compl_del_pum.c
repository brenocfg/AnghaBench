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
 int /*<<< orphan*/ * compl_match_array ; 
 int /*<<< orphan*/  pum_undisplay () ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ins_compl_del_pum()
{
    if (compl_match_array != NULL)
    {
	pum_undisplay();
	vim_free(compl_match_array);
	compl_match_array = NULL;
    }
}