#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_get_property_cookie_t ;
typedef  int /*<<< orphan*/ * gpointer ;
struct TYPE_5__ {int /*<<< orphan*/  last_timestamp; int /*<<< orphan*/  ewmh; int /*<<< orphan*/  screen_nbr; int /*<<< orphan*/  sndisplay; } ;
struct TYPE_4__ {int /*<<< orphan*/  command; int /*<<< orphan*/ * wmclass; int /*<<< orphan*/ * app_id; int /*<<< orphan*/ * icon; int /*<<< orphan*/ * binary; int /*<<< orphan*/  description; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  SnLauncherContext ;
typedef  TYPE_1__ RofiHelperExecuteContext ;
typedef  scalar_t__ GSpawnChildSetupFunc ;

/* Variables and functions */
 int /*<<< orphan*/  sn_launcher_context_initiate (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sn_launcher_context_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sn_launcher_context_set_application_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sn_launcher_context_set_binary_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sn_launcher_context_set_description (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sn_launcher_context_set_icon_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sn_launcher_context_set_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sn_launcher_context_set_wmclass (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sn_launcher_context_set_workspace (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ sn_launcher_context_setup_child_process ; 
 TYPE_2__* xcb ; 
 int /*<<< orphan*/  xcb_ewmh_get_current_desktop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xcb_ewmh_get_current_desktop_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *) ; 

void display_startup_notification ( RofiHelperExecuteContext *context, GSpawnChildSetupFunc *child_setup, gpointer *user_data )
{
    if ( context == NULL ) {
        return;
    }

    SnLauncherContext *sncontext;

    sncontext = sn_launcher_context_new ( xcb->sndisplay, xcb->screen_nbr );

    sn_launcher_context_set_name ( sncontext, context->name );
    sn_launcher_context_set_description ( sncontext, context->description );
    if ( context->binary != NULL ) {
        sn_launcher_context_set_binary_name ( sncontext, context->binary );
    }
    if ( context->icon != NULL ) {
        sn_launcher_context_set_icon_name ( sncontext, context->icon );
    }
    if ( context->app_id != NULL ) {
        sn_launcher_context_set_application_id ( sncontext, context->app_id );
    }
    if ( context->wmclass != NULL ) {
        sn_launcher_context_set_wmclass ( sncontext, context->wmclass );
    }

    xcb_get_property_cookie_t c;
    unsigned int              current_desktop = 0;

    c = xcb_ewmh_get_current_desktop ( &xcb->ewmh, xcb->screen_nbr );
    if ( xcb_ewmh_get_current_desktop_reply ( &xcb->ewmh, c, &current_desktop, NULL ) ) {
        sn_launcher_context_set_workspace ( sncontext, current_desktop );
    }

    sn_launcher_context_initiate ( sncontext, "rofi", context->command, xcb->last_timestamp );

    *child_setup = (GSpawnChildSetupFunc) sn_launcher_context_setup_child_process;
    *user_data   = sncontext;
}