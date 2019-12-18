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
 char* Trim (char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char const*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static int ConcatenatedIndex( char *psz_haystack, const char *psz_needle )
{
    char *psz_family = psz_haystack;
    char *psz_terminator = psz_haystack + strlen( psz_haystack );
    int i_index = 0;

    while( psz_family < psz_terminator )
    {
        char *psz_amp = strchr( psz_family, '&' );

        if( !psz_amp ) psz_amp = psz_terminator;

        *psz_amp = 0;

        psz_family = Trim( psz_family );
        if( !strcasecmp( psz_family, psz_needle ) )
            return i_index;

        psz_family = psz_amp + 1;
        ++i_index;
    }

    return -1;
}