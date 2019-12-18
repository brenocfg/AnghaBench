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
struct TYPE_6__ {int /*<<< orphan*/  drawarea; } ;
struct TYPE_5__ {scalar_t__ info; } ;
typedef  TYPE_1__ GtkTargetEntry ;

/* Variables and functions */
 int GDK_ACTION_COPY ; 
 int GDK_ACTION_MOVE ; 
 int /*<<< orphan*/  GTK_DEST_DEFAULT_ALL ; 
 int N_DND_TARGETS ; 
 scalar_t__ TARGET_HTML ; 
 int /*<<< orphan*/  clip_html ; 
 TYPE_1__* dnd_targets ; 
 int /*<<< orphan*/  gtk_drag_dest_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  gtk_drag_dest_unset (int /*<<< orphan*/ ) ; 
 TYPE_2__ gui ; 

void
gui_gtk_set_dnd_targets(void)
{
    int		    i, j = 0;
    int		    n_targets = N_DND_TARGETS;
    GtkTargetEntry  targets[N_DND_TARGETS];

    for (i = 0; i < (int)N_DND_TARGETS; ++i)
    {
	if (!clip_html && dnd_targets[i].info == TARGET_HTML)
	    n_targets--;
	else
	    targets[j++] = dnd_targets[i];
    }

    gtk_drag_dest_unset(gui.drawarea);
    gtk_drag_dest_set(gui.drawarea,
		      GTK_DEST_DEFAULT_ALL,
		      targets, n_targets,
		      GDK_ACTION_COPY | GDK_ACTION_MOVE);
}