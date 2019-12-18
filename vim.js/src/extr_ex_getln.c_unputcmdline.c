#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cmdlen; scalar_t__ cmdpos; scalar_t__ cmdbuff; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ ccline ; 
 scalar_t__ cmd_silent ; 
 int /*<<< orphan*/  cursorcmd () ; 
 int /*<<< orphan*/  draw_cmdline (scalar_t__,int) ; 
 scalar_t__ has_mbyte ; 
 int mb_ptr2len (scalar_t__) ; 
 int /*<<< orphan*/  msg_no_more ; 
 int /*<<< orphan*/  msg_putchar (char) ; 
 int stub1 (scalar_t__) ; 

void
unputcmdline()
{
    if (cmd_silent)
	return;
    msg_no_more = TRUE;
    if (ccline.cmdlen == ccline.cmdpos)
	msg_putchar(' ');
#ifdef FEAT_MBYTE
    else if (has_mbyte)
	draw_cmdline(ccline.cmdpos,
			       (*mb_ptr2len)(ccline.cmdbuff + ccline.cmdpos));
#endif
    else
	draw_cmdline(ccline.cmdpos, 1);
    msg_no_more = FALSE;
    cursorcmd();
}