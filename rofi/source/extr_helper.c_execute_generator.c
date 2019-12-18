#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  run_command; } ;
struct TYPE_5__ {int /*<<< orphan*/  message; } ;
typedef  TYPE_1__ GError ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  G_SPAWN_SEARCH_PATH ; 
 TYPE_4__ config ; 
 int /*<<< orphan*/  g_error_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_spawn_async_with_pipes (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,TYPE_1__**) ; 
 char* g_strdup_printf (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strfreev (char**) ; 
 int /*<<< orphan*/  helper_parse_setup (int /*<<< orphan*/ ,char***,int*,char*,char const*,char*) ; 
 int /*<<< orphan*/  rofi_view_error_dialog (char*,int /*<<< orphan*/ ) ; 

int execute_generator ( const char * cmd )
{
    char **args = NULL;
    int  argv   = 0;
    helper_parse_setup ( config.run_command, &args, &argv, "{cmd}", cmd, (char *) 0 );

    int    fd     = -1;
    GError *error = NULL;
    g_spawn_async_with_pipes ( NULL, args, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL, &fd, NULL, &error );

    if ( error != NULL ) {
        char *msg = g_strdup_printf ( "Failed to execute: '%s'\nError: '%s'", cmd, error->message );
        rofi_view_error_dialog ( msg, FALSE );
        g_free ( msg );
        // print error.
        g_error_free ( error );
        fd = -1;
    }
    g_strfreev ( args );
    return fd;
}