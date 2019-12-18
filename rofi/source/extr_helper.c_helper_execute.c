#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * gpointer ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_4__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  RofiHelperExecuteContext ;
typedef  int /*<<< orphan*/ * GSpawnChildSetupFunc ;
typedef  TYPE_1__ GError ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  G_SPAWN_SEARCH_PATH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  display_startup_notification (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_error_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_spawn_async (char const*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 char* g_strdup_printf (char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strfreev (char**) ; 
 int /*<<< orphan*/  rofi_view_error_dialog (char*,int /*<<< orphan*/ ) ; 

gboolean helper_execute ( const char *wd, char **args, const char *error_precmd, const char *error_cmd, RofiHelperExecuteContext *context )
{
    gboolean             retv   = TRUE;
    GError               *error = NULL;

    GSpawnChildSetupFunc child_setup = NULL;
    gpointer             user_data   = NULL;

    display_startup_notification ( context, &child_setup, &user_data );

    g_spawn_async ( wd, args, NULL, G_SPAWN_SEARCH_PATH, child_setup, user_data, NULL, &error );
    if ( error != NULL ) {
        char *msg = g_strdup_printf ( "Failed to execute: '%s%s'\nError: '%s'", error_precmd, error_cmd, error->message );
        rofi_view_error_dialog ( msg, FALSE  );
        g_free ( msg );
        // print error.
        g_error_free ( error );
        retv = FALSE;
    }

    // Free the args list.
    g_strfreev ( args );
    return retv;
}