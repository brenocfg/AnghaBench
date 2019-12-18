#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lnum; } ;
struct TYPE_4__ {TYPE_1__ w_cursor; int /*<<< orphan*/  w_wcol; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PC_STATUS_LEFT ; 
 scalar_t__ PC_STATUS_RIGHT ; 
 scalar_t__ PC_STATUS_UNSET ; 
 TYPE_2__* curwin ; 
 scalar_t__ msg_scrolled ; 
 int /*<<< orphan*/  pc_attr ; 
 int /*<<< orphan*/  pc_bytes ; 
 int /*<<< orphan*/  pc_col ; 
 scalar_t__ pc_row ; 
 scalar_t__ pc_status ; 
 int /*<<< orphan*/  redrawWinline (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_puts (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
edit_unputchar()
{
    if (pc_status != PC_STATUS_UNSET && pc_row >= msg_scrolled)
    {
#if defined(FEAT_MBYTE)
	if (pc_status == PC_STATUS_RIGHT)
	    ++curwin->w_wcol;
	if (pc_status == PC_STATUS_RIGHT || pc_status == PC_STATUS_LEFT)
	    redrawWinline(curwin->w_cursor.lnum, FALSE);
	else
#endif
	    screen_puts(pc_bytes, pc_row - msg_scrolled, pc_col, pc_attr);
    }
}