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
 int /*<<< orphan*/  g_warning (char*,char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strtol (char const*,int /*<<< orphan*/ *,int) ; 

char helper_parse_char ( const char *arg )
{
    const size_t len = strlen ( arg );
    // If the length is 1, it is not escaped.
    if ( len == 1 ) {
        return arg[0];
    }
    // If the length is 2 and the first character is '\', we unescape it.
    if ( len == 2 && arg[0] == '\\' ) {
        switch ( arg[1] )
        {
        // New line
        case 'n': return '\n';
        // Bell
        case  'a': return '\a';
        // Backspace
        case 'b': return '\b';
        // Tab
        case  't': return '\t';
        // Vertical tab
        case  'v': return '\v';
        // Form feed
        case  'f': return '\f';
        // Carriage return
        case  'r': return '\r';
        // Forward slash
        case  '\\': return '\\';
        // 0 line.
        case  '0': return '\0';
        default:
            break;
        }
    }
    if ( len > 2 && arg[0] == '\\' && arg[1] == 'x' ) {
        return (char) strtol ( &arg[2], NULL, 16 );
    }
    g_warning ( "Failed to parse character string: \"%s\"", arg );
    // for now default to newline.
    return '\n';
}