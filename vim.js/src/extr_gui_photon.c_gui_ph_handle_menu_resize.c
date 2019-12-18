#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* int_u ;
struct TYPE_12__ {int /*<<< orphan*/ * vimContainer; int /*<<< orphan*/ * vimPanelGroup; void* toolbar_height; void* menu_height; scalar_t__ menu_is_active; } ;
struct TYPE_11__ {void* y; scalar_t__ x; } ;
struct TYPE_10__ {TYPE_2__* cbdata; } ;
struct TYPE_8__ {void* h; } ;
struct TYPE_9__ {TYPE_1__ new_dim; } ;
typedef  int /*<<< orphan*/  PtWidget_t ;
typedef  TYPE_2__ PtContainerCallback_t ;
typedef  TYPE_3__ PtCallbackInfo_t ;
typedef  TYPE_4__ PhPoint_t ;

/* Variables and functions */
 int /*<<< orphan*/  PtSetResource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pt_ARG_POS ; 
 int Pt_CONTINUE ; 
 TYPE_6__ gui ; 
 int /*<<< orphan*/  gui_ph_get_panelgroup_margins (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gui_ph_resize_container () ; 
 int /*<<< orphan*/  pg_margin_bottom ; 
 int /*<<< orphan*/  pg_margin_left ; 
 int /*<<< orphan*/  pg_margin_right ; 
 int /*<<< orphan*/  pg_margin_top ; 

__attribute__((used)) static int
gui_ph_handle_menu_resize(
	PtWidget_t *widget,
	void *other,
	PtCallbackInfo_t *info)
{
    PtContainerCallback_t *sizes = info->cbdata;
    PtWidget_t		*container;
    PhPoint_t		below_menu;
    int_u		height;

    height = sizes->new_dim.h;

    /* Because vim treats the toolbar and menubar separately,
     * and here they're lumped together into a PtToolbarGroup,
     * we only need either menu_height or toolbar_height set at once */
    if (gui.menu_is_active)
    {
	gui.menu_height = height;
	gui.toolbar_height = 0;
    }
#ifdef FEAT_TOOLBAR
    else
	gui.toolbar_height = height;
#endif

    below_menu.x = 0;
    below_menu.y = height;

#ifdef USE_PANEL_GROUP
    container = gui.vimPanelGroup;
#else
    container = gui.vimContainer;
#endif

    PtSetResource(container, Pt_ARG_POS, &below_menu, 0);

    gui_ph_resize_container();

#ifdef USE_PANEL_GROUP
    gui_ph_get_panelgroup_margins(
	    &pg_margin_top, &pg_margin_bottom,
	    &pg_margin_left, &pg_margin_right);
#endif
    return Pt_CONTINUE;
}