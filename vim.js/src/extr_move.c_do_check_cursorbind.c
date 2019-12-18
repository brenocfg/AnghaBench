#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* coladd; void* col; int /*<<< orphan*/  lnum; } ;
struct TYPE_6__ {int w_set_curswant; void* w_redr_status; int /*<<< orphan*/  w_p_scb; void* w_curswant; TYPE_1__ w_cursor; scalar_t__ w_p_diff; scalar_t__ w_p_crb; int /*<<< orphan*/ * w_buffer; struct TYPE_6__* w_next; } ;
typedef  TYPE_2__ win_T ;
typedef  int /*<<< orphan*/  linenr_T ;
typedef  void* colnr_T ;
typedef  int /*<<< orphan*/  buf_T ;

/* Variables and functions */
 void* TRUE ; 
 int /*<<< orphan*/  VALID ; 
 int VIsual_active ; 
 int VIsual_select ; 
 int /*<<< orphan*/  check_cursor () ; 
 int /*<<< orphan*/ * curbuf ; 
 TYPE_2__* curwin ; 
 int /*<<< orphan*/  diff_get_corresponding_line (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* firstwin ; 
 scalar_t__ has_mbyte ; 
 int /*<<< orphan*/  mb_adjust_cursor () ; 
 int /*<<< orphan*/  redraw_later (int /*<<< orphan*/ ) ; 
 int restart_edit ; 
 int /*<<< orphan*/  update_topline () ; 

void
do_check_cursorbind()
{
    linenr_T	line = curwin->w_cursor.lnum;
    colnr_T	col = curwin->w_cursor.col;
# ifdef FEAT_VIRTUALEDIT
    colnr_T	coladd = curwin->w_cursor.coladd;
# endif
    colnr_T	curswant = curwin->w_curswant;
    int		set_curswant = curwin->w_set_curswant;
    win_T	*old_curwin = curwin;
    buf_T	*old_curbuf = curbuf;
    int		restart_edit_save;
# ifdef FEAT_VISUAL
    int		old_VIsual_select = VIsual_select;
    int		old_VIsual_active = VIsual_active;
# endif

    /*
     * loop through the cursorbound windows
     */
# ifdef FEAT_VISUAL
    VIsual_select = VIsual_active = 0;
# endif
    for (curwin = firstwin; curwin; curwin = curwin->w_next)
    {
	curbuf = curwin->w_buffer;
	/* skip original window  and windows with 'noscrollbind' */
	if (curwin != old_curwin && curwin->w_p_crb)
	{
# ifdef FEAT_DIFF
	    if (curwin->w_p_diff)
		curwin->w_cursor.lnum
			= diff_get_corresponding_line(old_curbuf,
						      line,
						      curbuf,
						      curwin->w_cursor.lnum);
	    else
# endif
		curwin->w_cursor.lnum = line;
	    curwin->w_cursor.col = col;
# ifdef FEAT_VIRTUALEDIT
	    curwin->w_cursor.coladd = coladd;
# endif
	    curwin->w_curswant = curswant;
	    curwin->w_set_curswant = set_curswant;

	    /* Make sure the cursor is in a valid position.  Temporarily set
	     * "restart_edit" to allow the cursor to be beyond the EOL. */
	    restart_edit_save = restart_edit;
	    restart_edit = TRUE;
	    check_cursor();
	    restart_edit = restart_edit_save;
# ifdef FEAT_MBYTE
	    /* Correct cursor for multi-byte character. */
	    if (has_mbyte)
		mb_adjust_cursor();
# endif
	    redraw_later(VALID);

	    /* Only scroll when 'scrollbind' hasn't done this. */
	    if (!curwin->w_p_scb)
		update_topline();
# ifdef FEAT_WINDOWS
	    curwin->w_redr_status = TRUE;
# endif
	}
    }

    /*
     * reset current-window
     */
# ifdef FEAT_VISUAL
    VIsual_select = old_VIsual_select;
    VIsual_active = old_VIsual_active;
# endif
    curwin = old_curwin;
    curbuf = old_curbuf;
}