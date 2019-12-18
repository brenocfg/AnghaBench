#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int gint64 ;
typedef  char gchar ;
struct TYPE_6__ {int port; int /*<<< orphan*/ * hostname; } ;
typedef  TYPE_1__ SshEntry ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_ascii_strcasecmp (char*,int /*<<< orphan*/ *) ; 
 int g_ascii_strtoll (char*,char**,int) ; 
 int /*<<< orphan*/  g_debug (char*,char const*) ; 
 TYPE_1__* g_realloc (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/ * g_strdup (char*) ; 
 char* g_strerror (scalar_t__) ; 
 char* g_strstrip (char*) ; 
 int /*<<< orphan*/  g_warning (char*,char*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 char* strsep (char**,char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static SshEntry *read_known_hosts_file ( const char *path, SshEntry * retv, unsigned int *length )
{
    FILE *fd   = fopen ( path, "r" );
    if ( fd != NULL ) {
        char   *buffer       = NULL;
        size_t buffer_length = 0;
        // Reading one line per time.
        while ( getline ( &buffer, &buffer_length, fd ) > 0 ) {
            // Strip whitespace.
            char *start = g_strstrip(&(buffer[0]));
            // Find start.
            if ( *start == '#' || *start == '@' ){
                // skip comments or cert-authority or revoked items.
                continue;
            }
            if ( *start == '|' ) {
                // Skip hashed hostnames.
                continue;
            }
            // Find end of hostname set.
            char *end  = strstr ( start, " " );
            if ( end == NULL  ) {
                // Something is wrong.
                continue;
            }
            *end = '\0';
            char *sep = start;
            start = strsep(&sep,", " );
            while (  start )
            {
                int port = 0;
                if ( start[0] == '[' ) {
                    start++;
                    char *end = strchr ( start, ']');
                    if ( end[1] == ':' ){
                        *end  = '\0';
                        errno = 0;
                        gchar *endptr = NULL;
                        gint64 number = g_ascii_strtoll ( &(end[2]), &endptr, 10);
                        if ( errno != 0  ) {
                            g_warning ( "Failed to parse port number: %s.", &(end[2]) );
                        } else if ( endptr == &(end[2])) {
                            g_warning ( "Failed to parse port number: %s, invalid number.", &(end[2]) );
                        } else if ( number < 0 || number > 65535 ) {
                            g_warning ( "Failed to parse port number: %s, out of range.", &(end[2]) );
                        } else {
                            port = number;
                        }
                    }
                }
                // Is this host name already in the list?
                // We often get duplicates in hosts file, so lets check this.
                int found = 0;
                for ( unsigned int j = 0; j < ( *length ); j++ ) {
                    if ( !g_ascii_strcasecmp ( start, retv[j].hostname ) ) {
                        found = 1;
                        break;
                    }
                }

                if ( !found ) {
                    // Add this host name to the list.
                    retv                           = g_realloc ( retv, ( ( *length ) + 2 ) * sizeof ( SshEntry ) );
                    retv[( *length )].hostname     = g_strdup ( start );
                    retv[( *length )].port         = port;
                    retv[( *length ) + 1].hostname = NULL;
                    retv[( *length ) + 1].port     = 0;
                    ( *length )++;
                }
                start = strsep(&sep,", " );
            }
        }
        if ( buffer != NULL ) {
            free ( buffer );
        }
        if ( fclose ( fd ) != 0 ) {
            g_warning ( "Failed to close hosts file: '%s'", g_strerror ( errno ) );
        }
    } else {
        g_debug ( "Failed to open KnownHostFile: '%s'", path );
    }

    return retv;
}