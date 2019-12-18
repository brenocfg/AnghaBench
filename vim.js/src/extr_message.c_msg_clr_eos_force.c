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
 scalar_t__ Columns ; 
 scalar_t__ Rows ; 
 scalar_t__* T_CD ; 
 scalar_t__* T_CE ; 
 scalar_t__ cmdmsg_rl ; 
 scalar_t__ full_screen ; 
 int msg_col ; 
 int msg_row ; 
 scalar_t__ msg_use_printf () ; 
 int /*<<< orphan*/  out_str (scalar_t__*) ; 
 int /*<<< orphan*/  screen_fill (int,int,int,int,char,char,int /*<<< orphan*/ ) ; 

void
msg_clr_eos_force()
{
    if (msg_use_printf())
    {
	if (full_screen)	/* only when termcap codes are valid */
	{
	    if (*T_CD)
		out_str(T_CD);	/* clear to end of display */
	    else if (*T_CE)
		out_str(T_CE);	/* clear to end of line */
	}
    }
    else
    {
#ifdef FEAT_RIGHTLEFT
	if (cmdmsg_rl)
	{
	    screen_fill(msg_row, msg_row + 1, 0, msg_col + 1, ' ', ' ', 0);
	    screen_fill(msg_row + 1, (int)Rows, 0, (int)Columns, ' ', ' ', 0);
	}
	else
#endif
	{
	    screen_fill(msg_row, msg_row + 1, msg_col, (int)Columns,
								 ' ', ' ', 0);
	    screen_fill(msg_row + 1, (int)Rows, 0, (int)Columns, ' ', ' ', 0);
	}
    }
}