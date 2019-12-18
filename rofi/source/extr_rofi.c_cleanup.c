#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  GString ;
typedef  TYPE_1__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  TIMINGS_STOP () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bindings ; 
 int /*<<< orphan*/ * config_path ; 
 int /*<<< orphan*/ * config_path_new ; 
 int /*<<< orphan*/  config_xresource_free () ; 
 int /*<<< orphan*/  display_cleanup () ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* g_list_first (scalar_t__) ; 
 int /*<<< orphan*/  g_list_free (scalar_t__) ; 
 TYPE_1__* g_list_next (TYPE_1__*) ; 
 int /*<<< orphan*/  g_main_loop_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ list_of_error_msgs ; 
 int /*<<< orphan*/ * main_loop ; 
 int /*<<< orphan*/  mode_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * modi ; 
 int /*<<< orphan*/  nk_bindings_free (int /*<<< orphan*/ ) ; 
 unsigned int num_modi ; 
 int /*<<< orphan*/  rofi_collect_modi_destroy () ; 
 int /*<<< orphan*/  rofi_icon_fetcher_destroy () ; 
 int /*<<< orphan*/ * rofi_theme ; 
 int /*<<< orphan*/  rofi_theme_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rofi_view_workers_finalize () ; 

__attribute__((used)) static void cleanup ()
{
    for ( unsigned int i = 0; i < num_modi; i++ ) {
        mode_destroy ( modi[i] );
    }
    rofi_view_workers_finalize ();
    if ( main_loop != NULL  ) {
        g_main_loop_unref ( main_loop );
        main_loop = NULL;
    }
    // Cleanup
    display_cleanup ();

    nk_bindings_free ( bindings );

    // Cleaning up memory allocated by the Xresources file.
    config_xresource_free ();
    g_free ( modi );

    g_free ( config_path );
    g_free ( config_path_new );

    if ( list_of_error_msgs ) {
        for ( GList *iter = g_list_first ( list_of_error_msgs );
              iter != NULL; iter = g_list_next ( iter ) ) {
            g_string_free ( (GString *) iter->data, TRUE );
        }
        g_list_free ( list_of_error_msgs );
    }

    if ( rofi_theme ) {
        rofi_theme_free ( rofi_theme );
        rofi_theme = NULL;
    }
    TIMINGS_STOP ();
    rofi_collect_modi_destroy ( );
    rofi_icon_fetcher_destroy ( );
}