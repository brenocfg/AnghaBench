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
struct TYPE_2__ {scalar_t__ starting; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ can_end_termcap_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_xterm_clip () ; 
 int /*<<< orphan*/  free_termoptions () ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  mch_restore_title (int) ; 
 int /*<<< orphan*/  mch_setmouse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stoptermcap () ; 

void
clear_termoptions()
{
    /*
     * Reset a few things before clearing the old options. This may cause
     * outputting a few things that the terminal doesn't understand, but the
     * screen will be cleared later, so this is OK.
     */
#ifdef FEAT_MOUSE_TTY
    mch_setmouse(FALSE);	    /* switch mouse off */
#endif
#ifdef FEAT_TITLE
    mch_restore_title(3);	    /* restore window titles */
#endif
#if defined(FEAT_XCLIPBOARD) && defined(FEAT_GUI)
    /* When starting the GUI close the display opened for the clipboard.
     * After restoring the title, because that will need the display. */
    if (gui.starting)
	clear_xterm_clip();
#endif
#ifdef WIN3264
    /*
     * Check if this is allowed now.
     */
    if (can_end_termcap_mode(FALSE) == TRUE)
#endif
	stoptermcap();			/* stop termcap mode */

    free_termoptions();
}