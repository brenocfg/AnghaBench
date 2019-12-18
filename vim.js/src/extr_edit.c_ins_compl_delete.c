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
 int CONT_ADDING ; 
 int /*<<< orphan*/  backspace_until_column (int) ; 
 int /*<<< orphan*/  changed_cline_bef_curs () ; 
 int compl_col ; 
 int compl_cont_status ; 
 int /*<<< orphan*/  compl_length ; 

__attribute__((used)) static void
ins_compl_delete()
{
    int	    i;

    /*
     * In insert mode: Delete the typed part.
     * In replace mode: Put the old characters back, if any.
     */
    i = compl_col + (compl_cont_status & CONT_ADDING ? compl_length : 0);
    backspace_until_column(i);
    changed_cline_bef_curs();
}