#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_xrm_database_t ;
struct TYPE_3__ {int /*<<< orphan*/  connection; } ;
typedef  TYPE_1__ xcb_stuff ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_XRESOURCES ; 
 int /*<<< orphan*/  __config_parse_xresource_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __config_parse_xresource_options_dynamic (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_xrm_database_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_xrm_database_from_default (int /*<<< orphan*/ ) ; 

void config_parse_xresource_options ( xcb_stuff *xcb )
{
    xcb_xrm_database_t *xDB = xcb_xrm_database_from_default ( xcb->connection );
    if ( xDB ) {
        __config_parse_xresource_options ( xDB, CONFIG_XRESOURCES );
        __config_parse_xresource_options_dynamic ( xDB, CONFIG_XRESOURCES );
        xcb_xrm_database_free ( xDB );
    }
}