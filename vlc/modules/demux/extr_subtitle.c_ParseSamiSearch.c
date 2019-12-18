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
typedef  int /*<<< orphan*/  text_t ;

/* Variables and functions */
 char* TextGetLine (int /*<<< orphan*/ *) ; 
 char* strcasestr (char const*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static const char *ParseSamiSearch( text_t *txt,
                                    const char *psz_start, const char *psz_str )
{
    if( psz_start && strcasestr( psz_start, psz_str ) )
    {
        const char *s = strcasestr( psz_start, psz_str );
        return &s[strlen( psz_str )];
    }

    for( ;; )
    {
        const char *p = TextGetLine( txt );
        if( !p )
            return NULL;

        const char *s = strcasestr( p, psz_str );
        if( s != NULL )
            return &s[strlen( psz_str )];
    }
}