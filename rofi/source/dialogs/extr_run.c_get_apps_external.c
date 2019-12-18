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
struct TYPE_2__ {int /*<<< orphan*/  run_list_command; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__ config ; 
 int /*<<< orphan*/  errno ; 
 int execute_generator (int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char** g_realloc (char**,unsigned int) ; 
 char* g_strdup (char*) ; 
 int /*<<< orphan*/  g_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char ** get_apps_external ( char **retv, unsigned int *length, unsigned int num_favorites )
{
    int fd = execute_generator ( config.run_list_command );
    if ( fd >= 0 ) {
        FILE *inp = fdopen ( fd, "r" );
        if ( inp ) {
            char   *buffer       = NULL;
            size_t buffer_length = 0;

            while ( getline ( &buffer, &buffer_length, inp ) > 0 ) {
                int found = 0;
                // Filter out line-end.
                if ( buffer[strlen ( buffer ) - 1] == '\n' ) {
                    buffer[strlen ( buffer ) - 1] = '\0';
                }

                // This is a nice little penalty, but doable? time will tell.
                // given num_favorites is max 25.
                for ( unsigned int j = 0; found == 0 && j < num_favorites; j++ ) {
                    if ( strcasecmp ( buffer, retv[j] ) == 0 ) {
                        found = 1;
                    }
                }

                if ( found == 1 ) {
                    continue;
                }

                // No duplicate, add it.
                retv              = g_realloc ( retv, ( ( *length ) + 2 ) * sizeof ( char* ) );
                retv[( *length )] = g_strdup ( buffer );

                ( *length )++;
            }
            if ( buffer != NULL ) {
                free ( buffer );
            }
            if ( fclose ( inp ) != 0 ) {
                g_warning ( "Failed to close stdout off executor script: '%s'",
                            g_strerror ( errno ) );
            }
        }
    }
    retv[( *length ) ] = NULL;
    return retv;
}