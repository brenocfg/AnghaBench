#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  combi_modi; } ;
struct TYPE_7__ {int /*<<< orphan*/ * mode; void* disable; } ;
struct TYPE_6__ {int num_switchers; TYPE_2__* switchers; } ;
typedef  int /*<<< orphan*/  Mode ;
typedef  TYPE_1__ CombiModePrivateData ;
typedef  TYPE_2__ CombiMode ;

/* Variables and functions */
 void* FALSE ; 
 TYPE_5__ config ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_realloc (TYPE_2__*,int) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_warning (char*,char*) ; 
 TYPE_1__* mode_get_private_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rofi_collect_modi_search (char*) ; 
 int /*<<< orphan*/ * script_switcher_parse_setup (char*) ; 
 char* strtok_r (char*,char const* const,char**) ; 

__attribute__((used)) static void combi_mode_parse_switchers ( Mode *sw )
{
    CombiModePrivateData *pd     = mode_get_private_data ( sw );
    char                 *savept = NULL;
    // Make a copy, as strtok will modify it.
    char                 *switcher_str = g_strdup ( config.combi_modi );
    const char * const   sep           = ",#";
    // Split token on ','. This modifies switcher_str.
    for ( char *token = strtok_r ( switcher_str, sep, &savept ); token != NULL;
          token = strtok_r ( NULL, sep, &savept ) ) {
        // Resize and add entry.
        pd->switchers = (CombiMode  *) g_realloc ( pd->switchers,
                                                   sizeof ( CombiMode ) * ( pd->num_switchers + 1 ) );

        Mode *mode = rofi_collect_modi_search ( token );
        if (  mode ) {
            pd->switchers[pd->num_switchers].disable = FALSE;
            pd->switchers[pd->num_switchers++].mode  = mode;
        }
        else {
            // If not build in, use custom switchers.
            Mode *sw = script_switcher_parse_setup ( token );
            if ( sw != NULL ) {
                pd->switchers[pd->num_switchers].disable = FALSE;
                pd->switchers[pd->num_switchers++].mode  = sw;
            }
            else {
                // Report error, don't continue.
                g_warning ( "Invalid script switcher: %s", token );
                token = NULL;
            }
        }
    }
    // Free string that was modified by strtok_r
    g_free ( switcher_str );
}