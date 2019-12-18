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
 int Columns ; 
 int Rows ; 
 int p_window ; 
 int /*<<< orphan*/  shell_new_columns () ; 
 int /*<<< orphan*/  shell_new_rows () ; 
 int /*<<< orphan*/  ui_new_shellsize () ; 

void
win_new_shellsize()
{
    static int	old_Rows = 0;
    static int	old_Columns = 0;

    if (old_Rows != Rows || old_Columns != Columns)
	ui_new_shellsize();
    if (old_Rows != Rows)
    {
	/* if 'window' uses the whole screen, keep it using that */
	if (p_window == old_Rows - 1 || old_Rows == 0)
	    p_window = Rows - 1;
	old_Rows = Rows;
	shell_new_rows();	/* update window sizes */
    }
    if (old_Columns != Columns)
    {
	old_Columns = Columns;
#ifdef FEAT_VERTSPLIT
	shell_new_columns();	/* update window sizes */
#endif
    }
}