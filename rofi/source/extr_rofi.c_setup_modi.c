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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_2__ {int /*<<< orphan*/  modi; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int add_mode (char*) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  help_print_mode_not_found (char*) ; 
 char* strtok_r (char*,char const* const,char**) ; 

__attribute__((used)) static gboolean setup_modi ( void )
{
    const char *const sep     = ",#";
    char              *savept = NULL;
    // Make a copy, as strtok will modify it.
    char              *switcher_str = g_strdup ( config.modi );
    // Split token on ','. This modifies switcher_str.
    for ( char *token = strtok_r ( switcher_str, sep, &savept ); token != NULL; token = strtok_r ( NULL, sep, &savept ) ) {
        if ( add_mode ( token ) == -1 ) {
            help_print_mode_not_found ( token );
        }
    }
    // Free string that was modified by strtok_r
    g_free ( switcher_str );
    return FALSE;
}