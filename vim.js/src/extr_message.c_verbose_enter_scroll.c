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
 scalar_t__ NUL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  msg_scroll ; 
 int /*<<< orphan*/  msg_silent ; 
 scalar_t__* p_vfile ; 

void
verbose_enter_scroll()
{
    if (*p_vfile != NUL)
	++msg_silent;
    else
	/* always scroll up, don't overwrite */
	msg_scroll = TRUE;
}