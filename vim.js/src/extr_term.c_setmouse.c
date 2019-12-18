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
struct TYPE_2__ {scalar_t__ in_use; } ;

/* Variables and functions */
 int ASKMORE ; 
 int CMDLINE ; 
 int CONFIRM ; 
 int EXTERNCMD ; 
 int /*<<< orphan*/  FALSE ; 
 int HITRETURN ; 
 int INSERT ; 
 int MOUSE_COMMAND ; 
 int MOUSE_INSERT ; 
 int MOUSE_NORMAL ; 
 int MOUSE_RETURN ; 
 int MOUSE_VISUAL ; 
 scalar_t__ NUL ; 
 int SETWSIZE ; 
 int State ; 
 scalar_t__ TMODE_RAW ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VIsual_active ; 
 scalar_t__ cur_tmode ; 
 TYPE_1__ gui ; 
 scalar_t__ has_mouse_termcode ; 
 int /*<<< orphan*/  mch_setmouse (int /*<<< orphan*/ ) ; 
 scalar_t__ mouse_has (int) ; 
 scalar_t__* p_mouse ; 
 int /*<<< orphan*/  update_mouseshape (int) ; 

void
setmouse()
{
# ifdef FEAT_MOUSE_TTY
    int	    checkfor;
# endif

# ifdef FEAT_MOUSESHAPE
    update_mouseshape(-1);
# endif

# ifdef FEAT_MOUSE_TTY /* Should be outside proc, but may break MOUSESHAPE */
#  ifdef FEAT_GUI
    /* In the GUI the mouse is always enabled. */
    if (gui.in_use)
	return;
#  endif
    /* be quick when mouse is off */
    if (*p_mouse == NUL || has_mouse_termcode == 0)
	return;

    /* don't switch mouse on when not in raw mode (Ex mode) */
    if (cur_tmode != TMODE_RAW)
    {
	mch_setmouse(FALSE);
	return;
    }

#  ifdef FEAT_VISUAL
    if (VIsual_active)
	checkfor = MOUSE_VISUAL;
    else
#  endif
	if (State == HITRETURN || State == ASKMORE || State == SETWSIZE)
	checkfor = MOUSE_RETURN;
    else if (State & INSERT)
	checkfor = MOUSE_INSERT;
    else if (State & CMDLINE)
	checkfor = MOUSE_COMMAND;
    else if (State == CONFIRM || State == EXTERNCMD)
	checkfor = ' '; /* don't use mouse for ":confirm" or ":!cmd" */
    else
	checkfor = MOUSE_NORMAL;    /* assume normal mode */

    if (mouse_has(checkfor))
	mch_setmouse(TRUE);
    else
	mch_setmouse(FALSE);
# endif
}