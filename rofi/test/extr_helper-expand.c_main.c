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
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  TASSERT (int) ; 
 int /*<<< orphan*/  cmd_set_arguments (int,char**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_get_home_dir () ; 
 char* rofi_expand_path (char*) ; 
 int /*<<< orphan*/ * setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char const*) ; 

int main ( int argc, char ** argv )
{
    cmd_set_arguments ( argc, argv );

    if ( setlocale ( LC_ALL, "" ) == NULL ) {
        fprintf ( stderr, "Failed to set locale.\n" );
        return EXIT_FAILURE;
    }

    /**
     * Test some path functions. Not easy as not sure what is right output on travis.
     */
    // Test if root is preserved.
    char *str = rofi_expand_path ( "/" );
    TASSERT ( strcmp ( str, "/" ) == 0 );
    g_free ( str );
    // Test is relative path is preserved.
    str = rofi_expand_path ( "../AUTHORS" );
    TASSERT ( strcmp ( str, "../AUTHORS" ) == 0 );
    g_free ( str );
    // Test another one.
    str = rofi_expand_path ( "/bin/false" );
    TASSERT ( strcmp ( str, "/bin/false" ) == 0 );
    g_free ( str );
    // See if user paths get expanded in full path.
    str = rofi_expand_path ( "~/" );
    const char *hd = g_get_home_dir ();
    TASSERT ( strcmp ( str, hd ) == 0 );
    g_free ( str );
    str = rofi_expand_path ( "~root/" );
    TASSERT ( str[0] == '/' );
    g_free ( str );
}