#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ gtk_sel_atom; } ;
struct TYPE_7__ {int /*<<< orphan*/  drawarea; } ;
struct TYPE_6__ {scalar_t__ info; } ;
typedef  TYPE_1__ GtkTargetEntry ;
typedef  int /*<<< orphan*/  GdkAtom ;

/* Variables and functions */
 scalar_t__ GDK_SELECTION_PRIMARY ; 
 int N_SELECTION_TARGETS ; 
 scalar_t__ TARGET_HTML ; 
 int /*<<< orphan*/  clip_html ; 
 TYPE_5__ clip_plus ; 
 int /*<<< orphan*/  gtk_selection_add_targets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  gtk_selection_clear_targets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ gui ; 
 TYPE_1__* selection_targets ; 

void
gui_gtk_set_selection_targets(void)
{
    int		    i, j = 0;
    int		    n_targets = N_SELECTION_TARGETS;
    GtkTargetEntry  targets[N_SELECTION_TARGETS];

    for (i = 0; i < (int)N_SELECTION_TARGETS; ++i)
    {
	/* OpenOffice tries to use TARGET_HTML and fails when we don't
	 * return something, instead of trying another target. Therefore only
	 * offer TARGET_HTML when it works. */
	if (!clip_html && selection_targets[i].info == TARGET_HTML)
	    n_targets--;
	else
	    targets[j++] = selection_targets[i];
    }

    gtk_selection_clear_targets(gui.drawarea, (GdkAtom)GDK_SELECTION_PRIMARY);
    gtk_selection_clear_targets(gui.drawarea, (GdkAtom)clip_plus.gtk_sel_atom);
    gtk_selection_add_targets(gui.drawarea,
			      (GdkAtom)GDK_SELECTION_PRIMARY,
			      targets, n_targets);
    gtk_selection_add_targets(gui.drawarea,
			      (GdkAtom)clip_plus.gtk_sel_atom,
			      targets, n_targets);
}