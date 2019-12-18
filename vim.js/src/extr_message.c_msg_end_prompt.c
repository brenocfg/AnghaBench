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
 int /*<<< orphan*/  cmdline_row ; 
 void* emsg_on_display ; 
 int lines_left ; 
 int /*<<< orphan*/  msg_clr_eos () ; 
 scalar_t__ msg_col ; 
 int /*<<< orphan*/  msg_row ; 
 void* need_wait_return ; 

void
msg_end_prompt()
{
    need_wait_return = FALSE;
    emsg_on_display = FALSE;
    cmdline_row = msg_row;
    msg_col = 0;
    msg_clr_eos();
    lines_left = -1;
}