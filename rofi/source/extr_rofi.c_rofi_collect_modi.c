#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  plugin_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  combi_mode ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  drun_mode ; 
 scalar_t__ find_arg (char*) ; 
 int /*<<< orphan*/  find_arg_str (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  help_keys_mode ; 
 int /*<<< orphan*/  rofi_collect_modi_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rofi_collect_modi_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_mode ; 
 int /*<<< orphan*/  ssh_mode ; 
 int /*<<< orphan*/  window_mode ; 
 int /*<<< orphan*/  window_mode_cd ; 

__attribute__((used)) static void rofi_collect_modi ( void )
{
#ifdef WINDOW_MODE
    rofi_collect_modi_add ( &window_mode );
    rofi_collect_modi_add ( &window_mode_cd );
#endif
    rofi_collect_modi_add ( &run_mode );
    rofi_collect_modi_add ( &ssh_mode );
#ifdef ENABLE_DRUN
    rofi_collect_modi_add ( &drun_mode );
#endif
    rofi_collect_modi_add ( &combi_mode );
    rofi_collect_modi_add ( &help_keys_mode );

    if ( find_arg ( "-no-plugins" ) < 0 ) {
        find_arg_str ( "-plugin-path", &( config.plugin_path ) );
        g_debug ( "Parse plugin path: %s", config.plugin_path );
        rofi_collect_modi_dir ( config.plugin_path );
    }
}