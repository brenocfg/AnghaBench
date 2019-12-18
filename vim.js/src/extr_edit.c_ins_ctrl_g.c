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
struct TYPE_2__ {int /*<<< orphan*/  w_cursor; } ;

/* Variables and functions */
#define  Ctrl_J 131 
#define  Ctrl_K 130 
 int /*<<< orphan*/  Insstart ; 
#define  K_DOWN 129 
#define  K_UP 128 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* curwin ; 
 int /*<<< orphan*/  ins_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ins_need_undo ; 
 int /*<<< orphan*/  ins_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  no_mapping ; 
 int plain_vgetc () ; 
 int /*<<< orphan*/  setcursor () ; 
 int /*<<< orphan*/  u_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vim_beep () ; 

__attribute__((used)) static void
ins_ctrl_g()
{
    int		c;

#ifdef FEAT_INS_EXPAND
    /* Right after CTRL-X the cursor will be after the ruler. */
    setcursor();
#endif

    /*
     * Don't map the second key. This also prevents the mode message to be
     * deleted when ESC is hit.
     */
    ++no_mapping;
    c = plain_vgetc();
    --no_mapping;
    switch (c)
    {
	/* CTRL-G k and CTRL-G <Up>: cursor up to Insstart.col */
	case K_UP:
	case Ctrl_K:
	case 'k': ins_up(TRUE);
		  break;

	/* CTRL-G j and CTRL-G <Down>: cursor down to Insstart.col */
	case K_DOWN:
	case Ctrl_J:
	case 'j': ins_down(TRUE);
		  break;

	/* CTRL-G u: start new undoable edit */
	case 'u': u_sync(TRUE);
		  ins_need_undo = TRUE;

		  /* Need to reset Insstart, esp. because a BS that joins
		   * a line to the previous one must save for undo. */
		  Insstart = curwin->w_cursor;
		  break;

	/* Unknown CTRL-G command, reserved for future expansion. */
	default:  vim_beep();
    }
}