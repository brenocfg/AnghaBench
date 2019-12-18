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
struct passwd {int /*<<< orphan*/  pw_dir; } ;

/* Variables and functions */
 char const G_DIR_SEPARATOR ; 
 int /*<<< orphan*/  G_DIR_SEPARATOR_S ; 
 char* g_build_filenamev (char**) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_get_home_dir () ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_strfreev (char**) ; 
 char** g_strsplit (char const*,int /*<<< orphan*/ ,int) ; 
 struct passwd* getpwnam (char*) ; 

char *rofi_expand_path ( const char *input )
{
    char **str = g_strsplit ( input, G_DIR_SEPARATOR_S, -1 );
    for ( unsigned int i = 0; str && str[i]; i++ ) {
        // Replace ~ with current user homedir.
        if ( str[i][0] == '~' && str[i][1] == '\0' ) {
            g_free ( str[i] );
            str[i] = g_strdup ( g_get_home_dir () );
        }
        // If other user, ask getpwnam.
        else if ( str[i][0] == '~' ) {
            struct passwd *p = getpwnam ( &( str[i][1] ) );
            if ( p != NULL ) {
                g_free ( str[i] );
                str[i] = g_strdup ( p->pw_dir );
            }
        }
        else if ( i == 0 ) {
            char * s = str[i];
            if ( input[0] == G_DIR_SEPARATOR ) {
                str[i] = g_strdup_printf ( "%s%s", G_DIR_SEPARATOR_S, s );
                g_free ( s );
            }
        }
    }
    char *retv = g_build_filenamev ( str );
    g_strfreev ( str );
    return retv;
}