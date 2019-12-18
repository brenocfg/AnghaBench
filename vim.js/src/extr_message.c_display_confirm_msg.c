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
 int /*<<< orphan*/  HLF_M ; 
 int /*<<< orphan*/ * confirm_msg ; 
 int /*<<< orphan*/  confirm_msg_used ; 
 int /*<<< orphan*/  hl_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_puts_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
display_confirm_msg()
{
    /* avoid that 'q' at the more prompt truncates the message here */
    ++confirm_msg_used;
    if (confirm_msg != NULL)
	msg_puts_attr(confirm_msg, hl_attr(HLF_M));
    --confirm_msg_used;
}