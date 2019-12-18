#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t gl_pathc; char** gl_pathv; int /*<<< orphan*/  gl_offs; } ;
typedef  TYPE_1__ glob_t ;
typedef  char gchar ;
struct TYPE_9__ {int /*<<< orphan*/ * hostname; scalar_t__ port; } ;
typedef  TYPE_2__ SshEntry ;
typedef  int /*<<< orphan*/  SSHModePrivateData ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SSH_TOKEN_DELIM ; 
 int /*<<< orphan*/  add_known_hosts_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_ascii_strcasecmp (char*,int /*<<< orphan*/ *) ; 
 char* g_ascii_strdown (char*,int) ; 
 char* g_build_filename (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_debug (char*,char const*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_path_get_dirname (char const*) ; 
 int /*<<< orphan*/  g_path_is_absolute (char*) ; 
 TYPE_2__* g_realloc (TYPE_2__*,unsigned int) ; 
 scalar_t__ g_strcmp0 (char*,char*) ; 
 void* g_strdup (char*) ; 
 int /*<<< orphan*/  g_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ glob (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 char* rofi_expand_path (char*) ; 
 scalar_t__ strpbrk (char*,char const* const) ; 
 char* strtok_r (char*,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static void parse_ssh_config_file ( SSHModePrivateData *pd, const char *filename, SshEntry **retv, unsigned int *length, unsigned int num_favorites )
{
    FILE *fd = fopen ( filename, "r" );

    g_debug ( "Parsing ssh config file: %s", filename );
    if ( fd != NULL ) {
        char   *buffer         = NULL;
        size_t buffer_length   = 0;
        char   *strtok_pointer = NULL;
        while ( getline ( &buffer, &buffer_length, fd ) > 0 ) {
            // Each line is either empty, a comment line starting with a '#'
            // character or of the form "keyword [=] arguments", where there may
            // be multiple (possibly quoted) arguments separated by whitespace.
            // The keyword is separated from its arguments by whitespace OR by
            // optional whitespace and a '=' character.
            char *token = strtok_r ( buffer, SSH_TOKEN_DELIM, &strtok_pointer );
            // Skip empty lines and comment lines. Also skip lines where the
            // keyword is not "Host".
            if ( !token || *token == '#' ) {
                continue;
            }
            char *low_token = g_ascii_strdown(token, -1);
            if ( g_strcmp0 ( low_token, "include" ) == 0 ) {
                token = strtok_r ( NULL, SSH_TOKEN_DELIM, &strtok_pointer );
                g_debug ( "Found Include: %s", token );
                gchar *path      = rofi_expand_path ( token );
                gchar *full_path = NULL;
                if ( !g_path_is_absolute ( path ) ) {
                    char *dirname = g_path_get_dirname ( filename );
                    full_path = g_build_filename ( dirname, path, NULL );
                    g_free ( dirname );
                }
                else {
                    full_path = g_strdup ( path );
                }
                glob_t globbuf = { .gl_pathc = 0, .gl_pathv = NULL, .gl_offs = 0 };

                if ( glob ( full_path, 0, NULL, &globbuf ) == 0 ) {
                    for ( size_t iter = 0; iter < globbuf.gl_pathc; iter++ ) {
                        parse_ssh_config_file ( pd, globbuf.gl_pathv[iter], retv, length, num_favorites );
                    }
                }
                globfree ( &globbuf );

                g_free ( full_path );
                g_free ( path );
            }
            else if ( g_strcmp0 ( low_token, "userknownhostsfile" ) == 0 ) {
                while ( ( token = strtok_r ( NULL, SSH_TOKEN_DELIM, &strtok_pointer ) ) ) {
                    g_debug("Found extra UserKnownHostsFile: %s", token);
                    add_known_hosts_file ( pd, token );
                }
            }
            else if ( g_strcmp0 ( low_token, "host" ) == 0 ) {
                // Now we know that this is a "Host" line.
                // The "Host" keyword is followed by one more host names separated
                // by whitespace; while host names may be quoted with double quotes
                // to represent host names containing spaces, we don't support this
                // (how many host names contain spaces?).
                while ( ( token = strtok_r ( NULL, SSH_TOKEN_DELIM, &strtok_pointer ) ) ) {
                    // We do not want to show wildcard entries, as you cannot ssh to them.
                    const char *const sep = "*?";
                    if ( *token == '!' || strpbrk ( token, sep ) ) {
                        continue;
                    }

                    // If comment, skip from now on.
                    if ( *token == '#' ) {
                        break;
                    }

                    // Is this host name already in the history file?
                    // This is a nice little penalty, but doable? time will tell.
                    // given num_favorites is max 25.
                    int found = 0;
                    for ( unsigned int j = 0; j < num_favorites; j++ ) {
                        if ( !g_ascii_strcasecmp ( token, ( *retv )[j].hostname ) ) {
                            found = 1;
                            break;
                        }
                    }

                    if ( found ) {
                        continue;
                    }

                    // Add this host name to the list.
                    ( *retv )                           = g_realloc ( ( *retv ), ( ( *length ) + 2 ) * sizeof ( SshEntry ) );
                    ( *retv )[( *length )].hostname     = g_strdup ( token );
                    ( *retv )[( *length )].port         = 0;
                    ( *retv )[( *length ) + 1].hostname = NULL;
                    ( *length )++;
                }
            }
            g_free ( low_token );
        }
        if ( buffer != NULL ) {
            free ( buffer );
        }

        if ( fclose ( fd ) != 0 ) {
            g_warning ( "Failed to close ssh configuration file: '%s'", g_strerror ( errno ) );
        }
    }
}