#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_17__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ major_version; scalar_t__ minor_version; scalar_t__ output; } ;
typedef  TYPE_2__ xcb_randr_query_version_reply_t ;
typedef  int /*<<< orphan*/  xcb_randr_query_version_cookie_t ;
typedef  scalar_t__ xcb_randr_output_t ;
struct TYPE_24__ {scalar_t__ rem; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ xcb_randr_monitor_info_iterator_t ;
typedef  TYPE_2__ xcb_randr_get_screen_resources_current_reply_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_screen_resources_current_cookie_t ;
typedef  TYPE_2__ xcb_randr_get_output_primary_reply_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_output_primary_cookie_t ;
typedef  TYPE_2__ xcb_randr_get_monitors_reply_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_monitors_cookie_t ;
struct TYPE_25__ {int /*<<< orphan*/  monitor_id; struct TYPE_25__* next; int /*<<< orphan*/  primary; } ;
typedef  TYPE_7__ workarea ;
struct TYPE_22__ {int /*<<< orphan*/  root; } ;
struct TYPE_21__ {TYPE_7__* monitors; int /*<<< orphan*/  connection; TYPE_1__* screen; } ;

/* Variables and functions */
 scalar_t__ RANDR_PREF_MAJOR_VERSION ; 
 scalar_t__ RANDR_PREF_MINOR_VERSION ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ XCB_RANDR_MAJOR_VERSION ; 
 scalar_t__ XCB_RANDR_MINOR_VERSION ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  g_debug (char*,...) ; 
 int /*<<< orphan*/  x11_build_monitor_layout_xinerama () ; 
 TYPE_7__* x11_get_monitor_from_output (scalar_t__) ; 
 TYPE_7__* x11_get_monitor_from_randr_monitor (int /*<<< orphan*/ ) ; 
 scalar_t__ x11_is_extension_present (char*) ; 
 TYPE_17__* xcb ; 
 int /*<<< orphan*/  xcb_randr_get_monitors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ xcb_randr_get_monitors_monitors_iterator (TYPE_2__*) ; 
 TYPE_2__* xcb_randr_get_monitors_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_randr_get_output_primary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* xcb_randr_get_output_primary_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_randr_get_screen_resources_current (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* xcb_randr_get_screen_resources_current_outputs (TYPE_2__*) ; 
 int xcb_randr_get_screen_resources_current_outputs_length (TYPE_2__*) ; 
 TYPE_2__* xcb_randr_get_screen_resources_current_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_randr_monitor_info_next (TYPE_3__*) ; 
 int /*<<< orphan*/  xcb_randr_query_version (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_2__* xcb_randr_query_version_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void x11_build_monitor_layout ()
{
    if ( xcb->monitors ) {
        return;
    }
    // If RANDR is not available, try Xinerama
    if ( !x11_is_extension_present ( "RANDR" ) ) {
        // Check if xinerama is available.
        if ( x11_is_extension_present ( "XINERAMA" ) ) {
            g_debug ( "Query XINERAMA for monitor layout." );
            x11_build_monitor_layout_xinerama ();
            return;
        }
        g_debug ( "No RANDR or Xinerama available for getting monitor layout." );
        return;
    }
    g_debug ( "Query RANDR for monitor layout." );

    g_debug ( "Randr XCB api version: %d.%d.", XCB_RANDR_MAJOR_VERSION, XCB_RANDR_MINOR_VERSION );
#if  ( ( ( XCB_RANDR_MAJOR_VERSION == RANDR_PREF_MAJOR_VERSION ) && ( XCB_RANDR_MINOR_VERSION >= RANDR_PREF_MINOR_VERSION ) ) \
    || XCB_RANDR_MAJOR_VERSION > RANDR_PREF_MAJOR_VERSION  )
    xcb_randr_query_version_cookie_t cversion = xcb_randr_query_version ( xcb->connection,
                                                                          RANDR_PREF_MAJOR_VERSION, RANDR_PREF_MINOR_VERSION );
    xcb_randr_query_version_reply_t  *rversion = xcb_randr_query_version_reply ( xcb->connection, cversion, NULL );
    if ( rversion ) {
        g_debug ( "Found randr version: %d.%d", rversion->major_version, rversion->minor_version );
        // Check if we are 1.5 and up.
        if ( ( ( rversion->major_version == RANDR_PREF_MAJOR_VERSION ) && ( rversion->minor_version >= RANDR_PREF_MINOR_VERSION ) ) ||
             ( rversion->major_version > RANDR_PREF_MAJOR_VERSION ) ) {
            xcb_randr_get_monitors_cookie_t t       = xcb_randr_get_monitors ( xcb->connection, xcb->screen->root, 1 );
            xcb_randr_get_monitors_reply_t  *mreply = xcb_randr_get_monitors_reply ( xcb->connection, t, NULL );
            if ( mreply ) {
                xcb_randr_monitor_info_iterator_t iter = xcb_randr_get_monitors_monitors_iterator ( mreply );
                while ( iter.rem > 0 ) {
                    workarea *w = x11_get_monitor_from_randr_monitor ( iter.data );
                    if ( w ) {
                        w->next       = xcb->monitors;
                        xcb->monitors = w;
                    }
                    xcb_randr_monitor_info_next ( &iter );
                }
                free ( mreply );
            }
        }
        free ( rversion );
    }
#endif

    // If no monitors found.
    if ( xcb->monitors == NULL ) {
        xcb_randr_get_screen_resources_current_reply_t  *res_reply;
        xcb_randr_get_screen_resources_current_cookie_t src;
        src       = xcb_randr_get_screen_resources_current ( xcb->connection, xcb->screen->root );
        res_reply = xcb_randr_get_screen_resources_current_reply ( xcb->connection, src, NULL );
        if ( !res_reply ) {
            return;  //just report error
        }
        int                mon_num = xcb_randr_get_screen_resources_current_outputs_length ( res_reply );
        xcb_randr_output_t *ops    = xcb_randr_get_screen_resources_current_outputs ( res_reply );

        // Get primary.
        xcb_randr_get_output_primary_cookie_t pc      = xcb_randr_get_output_primary ( xcb->connection, xcb->screen->root );
        xcb_randr_get_output_primary_reply_t  *pc_rep = xcb_randr_get_output_primary_reply ( xcb->connection, pc, NULL );

        for ( int i = mon_num - 1; i >= 0; i-- ) {
            workarea *w = x11_get_monitor_from_output ( ops[i] );
            if ( w ) {
                w->next       = xcb->monitors;
                xcb->monitors = w;
                if ( pc_rep && pc_rep->output == ops[i] ) {
                    w->primary = TRUE;
                }
            }
        }
        // If exists, free primary output reply.
        if ( pc_rep ) {
            free ( pc_rep );
        }
        free ( res_reply );
    }

    // Number monitor
    int index = 0;
    for ( workarea *iter = xcb->monitors; iter; iter = iter->next ) {
        iter->monitor_id = index++;
    }
}