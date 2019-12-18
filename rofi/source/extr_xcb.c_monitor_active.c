#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* xcb_drawable_t ;
struct TYPE_9__ {char* name; scalar_t__ primary; struct TYPE_9__* next; } ;
typedef  TYPE_1__ workarea ;
typedef  scalar_t__ gint64 ;
struct TYPE_11__ {char* monitor; } ;
struct TYPE_10__ {TYPE_1__* monitors; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 TYPE_8__ config ; 
 void* g_ascii_strtoll (char*,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ g_str_has_prefix (char*,char*) ; 
 scalar_t__ g_strcmp0 (char*,char*) ; 
 int /*<<< orphan*/  g_warning (char*) ; 
 int monitor_active_from_id (scalar_t__,TYPE_1__*) ; 
 scalar_t__ monitor_active_from_winid (void*,TYPE_1__*) ; 
 int /*<<< orphan*/  monitor_dimensions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ monitor_get_dimension (scalar_t__,TYPE_1__*) ; 
 TYPE_2__* xcb ; 

int monitor_active ( workarea *mon )
{
    if ( config.monitor != NULL ) {
        for ( workarea *iter = xcb->monitors; iter; iter = iter->next ) {
            if ( g_strcmp0 ( config.monitor, iter->name ) == 0 ) {
                *mon = *iter;
                return TRUE;
            }
        }
    }
    // Grab primary.
    if ( g_strcmp0 ( config.monitor, "primary" ) == 0 ) {
        for ( workarea *iter = xcb->monitors; iter; iter = iter->next ) {
            if ( iter->primary ) {
                *mon = *iter;
                return TRUE;
            }
        }
    }
    if ( g_str_has_prefix ( config.monitor, "wid:" ) ) {
        char           *end = NULL;
        xcb_drawable_t win  = g_ascii_strtoll ( config.monitor + 4, &end, 0 );
        if ( end != config.monitor ) {
            if ( monitor_active_from_winid ( win, mon ) ) {
                return TRUE;
            }
        }
    }
    {
        // IF fail, fall back to classic mode.
        char   *end   = NULL;
        gint64 mon_id = g_ascii_strtoll ( config.monitor, &end, 0 );
        if ( end != config.monitor ) {
            if ( mon_id >= 0 ) {
                if ( monitor_get_dimension ( mon_id, mon ) ) {
                    return TRUE;
                }
                g_warning ( "Failed to find selected monitor." );
            }
            else {
                return monitor_active_from_id ( mon_id, mon );
            }
        }
    }
    // Fallback.
    monitor_dimensions ( 0, 0, mon );
    return FALSE;
}