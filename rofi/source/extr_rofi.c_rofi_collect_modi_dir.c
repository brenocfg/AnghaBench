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
typedef  int /*<<< orphan*/  gpointer ;
struct TYPE_3__ {scalar_t__ abi_version; int /*<<< orphan*/ * module; } ;
typedef  TYPE_1__ Mode ;
typedef  int /*<<< orphan*/  GModule ;
typedef  int /*<<< orphan*/  GDir ;

/* Variables and functions */
 scalar_t__ ABI_VERSION ; 
 int G_MODULE_BIND_LAZY ; 
 int G_MODULE_BIND_LOCAL ; 
 int /*<<< orphan*/  G_MODULE_SUFFIX ; 
 char* g_build_filename (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_dir_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* g_dir_read_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_module_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_module_error () ; 
 int /*<<< orphan*/ * g_module_open (char*,int) ; 
 scalar_t__ g_module_symbol (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_str_has_suffix (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_warning (char*,char const*,...) ; 
 int /*<<< orphan*/  rofi_collect_modi_add (TYPE_1__*) ; 

__attribute__((used)) static void rofi_collect_modi_dir ( const char *base_dir )
{
    GDir *dir = g_dir_open ( base_dir, 0, NULL );
    if ( dir ) {
        const char *dn = NULL;
        while ( ( dn = g_dir_read_name ( dir ) ) ) {
            if ( !g_str_has_suffix ( dn, G_MODULE_SUFFIX ) ) {
                continue;
            }
            char    *fn  = g_build_filename ( base_dir, dn, NULL );
            GModule *mod = g_module_open ( fn, G_MODULE_BIND_LAZY | G_MODULE_BIND_LOCAL );
            if ( mod ) {
                Mode *m = NULL;
                if ( g_module_symbol ( mod, "mode", (gpointer *) &m ) ) {
                    if ( m->abi_version != ABI_VERSION ) {
                        g_warning ( "ABI version of plugin: '%s' does not match: %08X expecting: %08X", dn, m->abi_version, ABI_VERSION );
                        g_module_close ( mod );
                    }
                    else {
                        m->module = mod;
                        if ( !rofi_collect_modi_add ( m ) ) {
                            g_module_close ( mod );
                        }
                    }
                }
                else {
                    g_warning ( "Symbol 'mode' not found in module: %s", dn );
                    g_module_close ( mod );
                }
            }
            else {
                g_warning ( "Failed to open 'mode' plugin: '%s', error: %s", dn, g_module_error () );
            }
            g_free ( fn );
        }
        g_dir_close ( dir );
    }
}