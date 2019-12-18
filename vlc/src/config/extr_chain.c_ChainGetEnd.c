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
 scalar_t__ IsEscape (char const*) ; 
 int /*<<< orphan*/  SKIPSPACE (char const*) ; 

__attribute__((used)) static const char *ChainGetEnd( const char *psz_string )
{
    const char *p = psz_string;
    char c;

    if( !psz_string )
        return NULL;

    /* Look for a opening character */
    SKIPSPACE( p );

    for( ;; p++)
    {
        if( *p == '\0' || *p == ',' || *p == '}' )
            return p;

        if( *p == '{' || *p == '"' || *p == '\'' )
            break;
    }

    /* Set c to the closing character */
    if( *p == '{' )
        c = '}';
    else
        c = *p;
    p++;

    /* Search the closing character, handle nested {..} */
    for( ;; )
    {
        if( *p == '\0')
            return p;

        if( IsEscape( p ) )
            p += 2;
        else if( *p == c )
            return ++p;
        else if( *p == '{' && c == '}' )
            p = ChainGetEnd( p );
        else
            p++;
    }
}