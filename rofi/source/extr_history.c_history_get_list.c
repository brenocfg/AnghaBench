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
struct TYPE_2__ {scalar_t__ disable_history; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 char** __history_get_element_list_fields (int /*<<< orphan*/ *,unsigned int*) ; 
 TYPE_1__ config ; 
 scalar_t__ errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_fopen (char const*,char*) ; 
 int /*<<< orphan*/  g_strerror (scalar_t__) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/ ) ; 

char ** history_get_list ( const char *filename, unsigned int *length )
{
    *length = 0;

    if ( config.disable_history ) {
        return NULL;
    }
    char **retv = NULL;
    // Open file.
    FILE *fd = g_fopen ( filename, "r" );
    if ( fd == NULL ) {
        // File that does not exists is not an error, so ignore it.
        // Everything else? panic.
        if ( errno != ENOENT ) {
            g_warning ( "Failed to open file: %s", g_strerror ( errno ) );
        }
        return NULL;
    }
    // Get list.
    retv = __history_get_element_list_fields ( fd, length );

    // Close file, if fails let user know on stderr.
    if ( fclose ( fd ) != 0 ) {
        g_warning ( "Failed to close history file: %s", g_strerror ( errno ) );
    }
    return retv;
}