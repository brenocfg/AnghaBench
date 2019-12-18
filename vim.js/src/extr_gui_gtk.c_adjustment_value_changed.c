#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* wp; TYPE_1__* id; } ;
typedef  TYPE_3__ scrollbar_T ;
typedef  scalar_t__ gpointer ;
struct TYPE_11__ {scalar_t__ value; } ;
struct TYPE_9__ {int w_topline; } ;
struct TYPE_8__ {int /*<<< orphan*/  window; } ;
typedef  TYPE_4__ GtkAdjustment ;
typedef  int /*<<< orphan*/  GdkModifierType ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  gdk_window_get_pointer (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_window_get_size (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  gui_drag_scrollbar (TYPE_3__*,long,int) ; 
 TYPE_3__* gui_find_scrollbar (long) ; 
 scalar_t__ im_is_preediting () ; 
 int /*<<< orphan*/  xim_reset () ; 

__attribute__((used)) static void
adjustment_value_changed(GtkAdjustment *adjustment, gpointer data)
{
    scrollbar_T	*sb;
    long	value;
    int		dragging = FALSE;

#ifdef FEAT_XIM
    /* cancel any preediting */
    if (im_is_preediting())
	xim_reset();
#endif

    sb = gui_find_scrollbar((long)data);
    value = (long)adjustment->value;
    /*
     * The dragging argument must be right for the scrollbar to work with
     * closed folds.  This isn't documented, hopefully this will keep on
     * working in later GTK versions.
     *
     * FIXME: Well, it doesn't work in GTK2. :)
     * HACK: Get the mouse pointer position, if it appears to be on an arrow
     * button set "dragging" to FALSE.  This assumes square buttons!
     */
    if (sb != NULL)
    {
	dragging = TRUE;

	if (sb->wp != NULL)
	{
	    int			x;
	    int			y;
	    GdkModifierType	state;
	    int			width;
	    int			height;

	    /* vertical scrollbar: need to set "dragging" properly in case
	     * there are closed folds. */
	    gdk_window_get_pointer(sb->id->window, &x, &y, &state);
	    gdk_window_get_size(sb->id->window, &width, &height);
	    if (x >= 0 && x < width && y >= 0 && y < height)
	    {
		if (y < width)
		{
		    /* up arrow: move one (closed fold) line up */
		    dragging = FALSE;
		    value = sb->wp->w_topline - 2;
		}
		else if (y > height - width)
		{
		    /* down arrow: move one (closed fold) line down */
		    dragging = FALSE;
		    value = sb->wp->w_topline;
		}
	    }
	}
    }

    gui_drag_scrollbar(sb, value, dragging);
}