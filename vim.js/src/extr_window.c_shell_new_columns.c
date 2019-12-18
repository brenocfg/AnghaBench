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
 scalar_t__ Columns ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  curwin ; 
 int /*<<< orphan*/ * firstwin ; 
 int /*<<< orphan*/  frame_check_width (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  frame_new_width (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ p_ea ; 
 int /*<<< orphan*/  topframe ; 
 int /*<<< orphan*/  win_comp_pos () ; 
 int /*<<< orphan*/  win_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 

void
shell_new_columns()
{
    if (firstwin == NULL)	/* not initialized yet */
	return;

    /* First try setting the widths of windows with 'winfixwidth'.  If that
     * doesn't result in the right width, forget about that option. */
    frame_new_width(topframe, (int)Columns, FALSE, TRUE);
    if (!frame_check_width(topframe, Columns))
	frame_new_width(topframe, (int)Columns, FALSE, FALSE);

    (void)win_comp_pos();		/* recompute w_winrow and w_wincol */
#if 0
    /* Disabled: don't want making the screen smaller make a window larger. */
    if (p_ea)
	win_equal(curwin, FALSE, 'h');
#endif
}