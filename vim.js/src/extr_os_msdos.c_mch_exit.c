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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TMODE_COOK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  mch_restore_cursor_shape (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_close_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_char (char) ; 
 int /*<<< orphan*/  out_flush () ; 
 int /*<<< orphan*/  set_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sys_cursor () ; 
 int /*<<< orphan*/  settmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stoptermcap () ; 

void
mch_exit(int r)
{
    settmode(TMODE_COOK);
    stoptermcap();
    set_interrupts(FALSE);	    /* restore interrupts */
#ifdef DJGPP
    set_sys_cursor();
#endif
    /* Somehow outputting CR-NL causes the original colors to be restored */
    out_char('\r');
    out_char('\n');
    out_flush();
    ml_close_all(TRUE);		    /* remove all memfiles */
#ifdef MCH_CURSOR_SHAPE
    mch_restore_cursor_shape(TRUE);
#endif
    exit(r);
}