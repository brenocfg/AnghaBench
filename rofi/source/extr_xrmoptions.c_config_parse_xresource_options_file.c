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
typedef  int /*<<< orphan*/  xcb_xrm_database_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_FILE ; 
 int /*<<< orphan*/  __config_parse_xresource_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __config_parse_xresource_options_dynamic (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_xrm_database_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_xrm_database_from_file (char const*) ; 

void config_parse_xresource_options_file ( const char *filename )
{
    if ( !filename ) {
        return;
    }
    // Map Xresource entries to rofi config options.
    xcb_xrm_database_t *xDB = xcb_xrm_database_from_file ( filename );
    if ( xDB == NULL ) {
        return;
    }
    __config_parse_xresource_options ( xDB, CONFIG_FILE );
    __config_parse_xresource_options_dynamic ( xDB, CONFIG_FILE );
    xcb_xrm_database_free ( xDB );
}