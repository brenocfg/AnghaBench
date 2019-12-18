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
 int /*<<< orphan*/  cmdline_row ; 
 int /*<<< orphan*/  msg_clr_eos_force () ; 
 scalar_t__ msg_col ; 
 int /*<<< orphan*/  msg_row ; 

void
msg_clr_cmdline()
{
    msg_row = cmdline_row;
    msg_col = 0;
    msg_clr_eos_force();
}