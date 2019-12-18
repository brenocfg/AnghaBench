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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fputc (char const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_shell_quote (char const*) ; 
 int /*<<< orphan*/  pango_parse_markup (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 

void rofi_output_formatted_line ( const char *format, const char *string, int selected_line, const char *filter )
{
    for ( int i = 0; format && format[i]; i++ ) {
        if ( format[i] == 'i' ) {
            fprintf ( stdout, "%d", selected_line );
        }
        else if ( format[i] == 'd' ) {
            fprintf ( stdout, "%d", ( selected_line + 1 ) );
        }
        else if ( format[i] == 's' ) {
            fputs ( string, stdout );
        }
        else if ( format[i] == 'p' ) {
            char *esc = NULL;
            pango_parse_markup(string, -1, 0, NULL, &esc, NULL, NULL);
            if ( esc ){
                fputs ( esc, stdout );
                g_free ( esc );
            } else {
                fputs ( "invalid string" , stdout );
            }
        }
        else if ( format[i] == 'q' ) {
            char *quote = g_shell_quote ( string );
            fputs ( quote, stdout );
            g_free ( quote );
        }
        else if ( format[i] == 'f' ) {
            if ( filter ) {
                fputs ( filter, stdout );
            }
        }
        else if ( format[i] == 'F' ) {
            if ( filter ) {
                char *quote = g_shell_quote ( filter );
                fputs ( quote, stdout );
                g_free ( quote );
            }
        }
        else {
            fputc ( format[i], stdout );
        }
    }
    fputc ( '\n', stdout );
    fflush ( stdout );
}