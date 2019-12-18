#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ fr_width; scalar_t__ fr_layout; int fr_height; struct TYPE_8__* fr_prev; TYPE_1__* fr_win; struct TYPE_8__* fr_parent; } ;
typedef  TYPE_2__ frame_T ;
struct TYPE_10__ {int tp_ch_used; } ;
struct TYPE_9__ {TYPE_2__* w_frame; } ;
struct TYPE_7__ {scalar_t__ w_p_wfh; } ;

/* Variables and functions */
 scalar_t__ Columns ; 
 int /*<<< orphan*/  EMSG (int /*<<< orphan*/ ) ; 
 scalar_t__ FR_LEAF ; 
 scalar_t__ NO_SCREEN ; 
 scalar_t__ Rows ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 scalar_t__ cmdline_row ; 
 TYPE_6__* curtab ; 
 int /*<<< orphan*/  e_noroom ; 
 int /*<<< orphan*/  frame_add_height (TYPE_2__*,int) ; 
 int frame_minheight (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ full_screen ; 
 TYPE_3__* lastwin ; 
 scalar_t__ msg_row ; 
 int p_ch ; 
 int /*<<< orphan*/  redraw_cmdline ; 
 int /*<<< orphan*/  screen_fill (int,int,int /*<<< orphan*/ ,int,char,char,int /*<<< orphan*/ ) ; 
 scalar_t__ starting ; 
 int /*<<< orphan*/  win_comp_pos () ; 
 int /*<<< orphan*/  win_setheight (scalar_t__) ; 

void
command_height()
{
#ifdef FEAT_WINDOWS
    int		h;
    frame_T	*frp;
    int		old_p_ch = curtab->tp_ch_used;

    /* Use the value of p_ch that we remembered.  This is needed for when the
     * GUI starts up, we can't be sure in what order things happen.  And when
     * p_ch was changed in another tab page. */
    curtab->tp_ch_used = p_ch;

    /* Find bottom frame with width of screen. */
    frp = lastwin->w_frame;
# ifdef FEAT_VERTSPLIT
    while (frp->fr_width != Columns && frp->fr_parent != NULL)
	frp = frp->fr_parent;
# endif

    /* Avoid changing the height of a window with 'winfixheight' set. */
    while (frp->fr_prev != NULL && frp->fr_layout == FR_LEAF
						      && frp->fr_win->w_p_wfh)
	frp = frp->fr_prev;

    if (starting != NO_SCREEN)
    {
	cmdline_row = Rows - p_ch;

	if (p_ch > old_p_ch)		    /* p_ch got bigger */
	{
	    while (p_ch > old_p_ch)
	    {
		if (frp == NULL)
		{
		    EMSG(_(e_noroom));
		    p_ch = old_p_ch;
		    curtab->tp_ch_used = p_ch;
		    cmdline_row = Rows - p_ch;
		    break;
		}
		h = frp->fr_height - frame_minheight(frp, NULL);
		if (h > p_ch - old_p_ch)
		    h = p_ch - old_p_ch;
		old_p_ch += h;
		frame_add_height(frp, -h);
		frp = frp->fr_prev;
	    }

	    /* Recompute window positions. */
	    (void)win_comp_pos();

	    /* clear the lines added to cmdline */
	    if (full_screen)
		screen_fill((int)(cmdline_row), (int)Rows, 0,
						   (int)Columns, ' ', ' ', 0);
	    msg_row = cmdline_row;
	    redraw_cmdline = TRUE;
	    return;
	}

	if (msg_row < cmdline_row)
	    msg_row = cmdline_row;
	redraw_cmdline = TRUE;
    }
    frame_add_height(frp, (int)(old_p_ch - p_ch));

    /* Recompute window positions. */
    if (frp != lastwin->w_frame)
	(void)win_comp_pos();
#else
    cmdline_row = Rows - p_ch;
    win_setheight(cmdline_row);
#endif
}