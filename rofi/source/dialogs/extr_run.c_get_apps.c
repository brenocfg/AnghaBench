#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dirent {scalar_t__ d_type; char* d_name; } ;
typedef  int /*<<< orphan*/  gsize ;
typedef  char gchar ;
typedef  scalar_t__ gboolean ;
struct TYPE_7__ {char* run_list_command; } ;
struct TYPE_6__ {char* message; } ;
typedef  TYPE_1__ GError ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_LNK ; 
 scalar_t__ DT_REG ; 
 scalar_t__ DT_UNKNOWN ; 
 int /*<<< orphan*/  G_FILE_TEST_IS_EXECUTABLE ; 
 char* RUN_CACHE_FILE ; 
 int /*<<< orphan*/  TICK_N (char*) ; 
 char const* cache_dir ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 TYPE_5__ config ; 
 char* g_build_filename (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_clear_error (TYPE_1__**) ; 
 int /*<<< orphan*/  g_debug (char*,char*) ; 
 scalar_t__ g_file_test (char*,int /*<<< orphan*/ ) ; 
 char* g_filename_to_utf8 (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char const* g_get_home_dir () ; 
 int /*<<< orphan*/ * g_getenv (char*) ; 
 char* g_locale_to_utf8 (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  g_qsort_with_data (char**,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char** g_realloc (char**,unsigned int) ; 
 scalar_t__ g_str_has_prefix (char*,char*) ; 
 scalar_t__ g_strcmp0 (char*,char*) ; 
 char* g_strdup (int /*<<< orphan*/ *) ; 
 char** get_apps_external (char**,unsigned int*,unsigned int) ; 
 char** history_get_list (char*,unsigned int*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 char* rofi_expand_path (char const*) ; 
 int /*<<< orphan*/  sort_func ; 
 char* strtok_r (char*,char const* const,char**) ; 

__attribute__((used)) static char ** get_apps ( unsigned int *length )
{
    GError       *error        = NULL;
    char         **retv        = NULL;
    unsigned int num_favorites = 0;
    char         *path;

    if ( g_getenv ( "PATH" ) == NULL ) {
        return NULL;
    }
    TICK_N ( "start" );
    path = g_build_filename ( cache_dir, RUN_CACHE_FILE, NULL );
    retv = history_get_list ( path, length );
    g_free ( path );
    // Keep track of how many where loaded as favorite.
    num_favorites = ( *length );

    path = g_strdup ( g_getenv ( "PATH" ) );

    gsize l        = 0;
    gchar *homedir = g_locale_to_utf8 (  g_get_home_dir (), -1, NULL, &l, &error );
    if ( error != NULL ) {
        g_debug ( "Failed to convert homedir to UTF-8: %s", error->message );
        g_clear_error ( &error );
        g_free ( homedir );
        return NULL;
    }

    const char *const sep                 = ":";
    char              *strtok_savepointer = NULL;
    for ( const char *dirname = strtok_r ( path, sep, &strtok_savepointer ); dirname != NULL; dirname = strtok_r ( NULL, sep, &strtok_savepointer ) ) {
        char *fpath = rofi_expand_path ( dirname );
        DIR  *dir   = opendir ( fpath );
        g_debug ( "Checking path %s for executable.", fpath );
        g_free ( fpath );

        if ( dir != NULL ) {
            struct dirent *dent;
            gsize         dirn_len = 0;
            gchar         *dirn    = g_locale_to_utf8 ( dirname, -1, NULL, &dirn_len, &error );
            if ( error != NULL ) {
                g_debug ( "Failed to convert directory name to UTF-8: %s", error->message );
                g_clear_error ( &error );
                closedir ( dir );
                continue;
            }
            gboolean is_homedir = g_str_has_prefix ( dirn, homedir );
            g_free ( dirn );

            while ( ( dent = readdir ( dir ) ) != NULL ) {
                if ( dent->d_type != DT_REG && dent->d_type != DT_LNK && dent->d_type != DT_UNKNOWN ) {
                    continue;
                }
                // Skip dot files.
                if ( dent->d_name[0] == '.' ) {
                    continue;
                }
                if ( is_homedir ) {
                    gchar    *fpath = g_build_filename ( dirname, dent->d_name, NULL );
                    gboolean b      = g_file_test ( fpath, G_FILE_TEST_IS_EXECUTABLE );
                    g_free ( fpath );
                    if ( !b ) {
                        continue;
                    }
                }

                gsize name_len;
                gchar *name = g_filename_to_utf8 ( dent->d_name, -1, NULL, &name_len, &error );
                if ( error != NULL ) {
                    g_debug ( "Failed to convert filename to UTF-8: %s", error->message );
                    g_clear_error ( &error );
                    g_free ( name );
                    continue;
                }
                // This is a nice little penalty, but doable? time will tell.
                // given num_favorites is max 25.
                int found = 0;
                for ( unsigned int j = 0; found == 0 && j < num_favorites; j++ ) {
                    if ( g_strcmp0 ( name, retv[j] ) == 0 ) {
                        found = 1;
                    }
                }

                if ( found == 1 ) {
                    g_free ( name );
                    continue;
                }

                retv                  = g_realloc ( retv, ( ( *length ) + 2 ) * sizeof ( char* ) );
                retv[( *length )]     = name;
                retv[( *length ) + 1] = NULL;
                ( *length )++;
            }

            closedir ( dir );
        }
    }
    g_free ( homedir );

    // Get external apps.
    if ( config.run_list_command != NULL && config.run_list_command[0] != '\0' ) {
        retv = get_apps_external ( retv, length, num_favorites );
    }
    // No sorting needed.
    if ( ( *length ) == 0 ) {
        return retv;
    }
    // TODO: check this is still fast enough. (takes 1ms on laptop.)
    if ( ( *length ) > num_favorites ) {
        g_qsort_with_data ( &retv[num_favorites], ( *length ) - num_favorites, sizeof ( char* ), sort_func, NULL );
    }
    g_free ( path );

    unsigned int removed = 0;
    for ( unsigned int index = num_favorites; index < ( ( *length ) - 1 ); index++ ) {
        if ( g_strcmp0 ( retv[index], retv[index + 1] ) == 0 ) {
            g_free ( retv[index] );
            retv[index] = NULL;
            removed++;
        }
    }

    if ( ( *length ) > num_favorites ) {
        g_qsort_with_data ( &retv[num_favorites], ( *length ) - num_favorites, sizeof ( char* ),
                            sort_func,
                            NULL );
    }
    // Reduce array length;
    ( *length ) -= removed;

    TICK_N ( "stop" );
    return retv;
}