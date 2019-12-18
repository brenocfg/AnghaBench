#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int w_wrow; } ;
typedef  TYPE_1__ win_T ;
struct TYPE_8__ {int char_width; int char_height; scalar_t__ in_use; } ;

/* Variables and functions */
 int Columns ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ W_ENDCOL (TYPE_1__*) ; 
 int W_WINROW (TYPE_1__*) ; 
 scalar_t__ Y_2_ROW (int) ; 
 TYPE_1__* curwin ; 
 TYPE_3__ gui ; 
 int /*<<< orphan*/  gui_mch_getmouse (int*,int*) ; 
 int /*<<< orphan*/  gui_mch_setmouse (int,int) ; 
 int /*<<< orphan*/  need_mouse_correct ; 
 scalar_t__ p_mousef ; 
 scalar_t__ tabline_height () ; 
 int /*<<< orphan*/  validate_cline_row () ; 
 TYPE_1__* xy2win (int,int) ; 

void
gui_mouse_correct()
{
    int		x, y;
    win_T	*wp = NULL;

    need_mouse_correct = FALSE;

    if (!(gui.in_use && p_mousef))
	return;

    gui_mch_getmouse(&x, &y);
    /* Don't move the mouse when it's left or right of the Vim window */
    if (x < 0 || x > Columns * gui.char_width)
	return;
    if (y >= 0
# ifdef FEAT_WINDOWS
	    && Y_2_ROW(y) >= tabline_height()
# endif
       )
	wp = xy2win(x, y);
    if (wp != curwin && wp != NULL)	/* If in other than current window */
    {
	validate_cline_row();
	gui_mch_setmouse((int)W_ENDCOL(curwin) * gui.char_width - 3,
		(W_WINROW(curwin) + curwin->w_wrow) * gui.char_height
						     + (gui.char_height) / 2);
    }
}