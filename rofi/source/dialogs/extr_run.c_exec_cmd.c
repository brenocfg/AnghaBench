#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gsize ;
typedef  char gchar ;
struct TYPE_7__ {int /*<<< orphan*/  message; } ;
struct TYPE_6__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ RofiHelperExecuteContext ;
typedef  TYPE_2__ GError ;

/* Variables and functions */
 int /*<<< orphan*/  RUN_CACHE_FILE ; 
 int /*<<< orphan*/  cache_dir ; 
 char* g_build_filename (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_error_free (TYPE_2__*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_locale_from_utf8 (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ helper_execute_command (int /*<<< orphan*/ *,char*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  history_remove (char*,char const*) ; 
 int /*<<< orphan*/  history_set (char*,char const*) ; 

__attribute__((used)) static void exec_cmd ( const char *cmd, int run_in_term )
{
    GError *error = NULL;
    if ( !cmd || !cmd[0] ) {
        return;
    }
    gsize lf_cmd_size = 0;
    gchar *lf_cmd     = g_locale_from_utf8 ( cmd, -1, NULL, &lf_cmd_size, &error );
    if ( error != NULL ) {
        g_warning ( "Failed to convert command to locale encoding: %s", error->message );
        g_error_free ( error );
        return;
    }

    char                     *path   = g_build_filename ( cache_dir, RUN_CACHE_FILE, NULL );
    RofiHelperExecuteContext context = { .name = NULL };
    // FIXME: assume startup notification support for terminals
    if (  helper_execute_command ( NULL, lf_cmd, run_in_term, run_in_term ? &context : NULL ) ) {
        /**
         * This happens in non-critical time (After launching app)
         * It is allowed to be a bit slower.
         */

        history_set ( path, cmd );
    }
    else {
        history_remove ( path, cmd );
    }
    g_free ( path );
    g_free ( lf_cmd );
}