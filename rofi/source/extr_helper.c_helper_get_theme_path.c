#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  G_FILE_TEST_EXISTS ; 
 int /*<<< orphan*/  THEME_DIR ; 
 char* g_build_filename (char const*,char*,char*,...) ; 
 int /*<<< orphan*/  g_debug (char*,char*) ; 
 scalar_t__ g_file_test (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_get_user_config_dir () ; 
 char* g_get_user_data_dir () ; 
 scalar_t__ g_str_has_suffix (char const*,char*) ; 
 char* g_strconcat (char const*,char*,int /*<<< orphan*/ *) ; 
 char* g_strdup (char const*) ; 
 char* rofi_expand_path (char const*) ; 

char *helper_get_theme_path ( const char *file )
{
    char *filename = rofi_expand_path ( file );
    g_debug ( "Opening theme, testing: %s\n", filename );
    if ( g_file_test ( filename, G_FILE_TEST_EXISTS ) ) {
        return filename;
    }
    g_free ( filename );

    if ( g_str_has_suffix ( file, ".rasi" ) ) {
        filename = g_strdup ( file );
    }
    else {
        filename = g_strconcat ( file, ".rasi", NULL );
    }
    // Check config's themes directory.
    const char *cpath = g_get_user_config_dir ();
    if ( cpath ) {
        char *themep = g_build_filename ( cpath, "rofi", "themes", filename, NULL );
        g_debug ( "Opening theme, testing: %s\n", themep );
        if ( themep && g_file_test ( themep, G_FILE_TEST_EXISTS ) ) {
            g_free ( filename );
            return themep;
        }
        g_free ( themep );
    }
    // Check config directory.
    if ( cpath ) {
        char *themep = g_build_filename ( cpath, "rofi", filename, NULL );
        g_debug ( "Opening theme, testing: %s\n", themep );
        if ( g_file_test ( themep, G_FILE_TEST_EXISTS ) ) {
            g_free ( filename );
            return themep;
        }
        g_free ( themep );
    }
    const char * datadir = g_get_user_data_dir ();
    if ( datadir ) {
        char *theme_path = g_build_filename ( datadir, "rofi", "themes", filename, NULL );
        g_debug ( "Opening theme, testing: %s\n", theme_path );
        if ( theme_path ) {
            if ( g_file_test ( theme_path, G_FILE_TEST_EXISTS ) ) {
                g_free ( filename );
                return theme_path;
            }
            g_free ( theme_path );
        }
    }

    char *theme_path = g_build_filename ( THEME_DIR, filename, NULL );
    if ( theme_path ) {
        g_debug ( "Opening theme, testing: %s\n", theme_path );
        if ( g_file_test ( theme_path, G_FILE_TEST_EXISTS ) ) {
            g_free ( filename );
            return theme_path;
        }
        g_free ( theme_path );
    }
    return filename;
}