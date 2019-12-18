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
typedef  char gchar ;

/* Variables and functions */
 char* g_regex_escape_string (char const*,int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static gchar *glob_to_regex ( const char *input )
{
    gchar  *r    = g_regex_escape_string ( input, -1 );
    size_t str_l = strlen ( r );
    for ( size_t i = 0; i < str_l; i++ ) {
        if ( r[i] == '\\' ) {
            if ( r[i + 1] == '*' ) {
                r[i] = '.';
            }
            else if ( r[i + 1] == '?' ) {
                r[i + 1] = 'S';
            }
            i++;
        }
    }
    return r;
}