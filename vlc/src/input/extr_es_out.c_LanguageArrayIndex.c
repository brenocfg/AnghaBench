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
 scalar_t__ strcasecmp (char const*,char const*) ; 

__attribute__((used)) static int LanguageArrayIndex( char **ppsz_langs, const char *psz_lang )
{
    if( !ppsz_langs || !psz_lang )
        return -1;

    for( int i = 0; ppsz_langs[i]; i++ )
    {
        if( !strcasecmp( ppsz_langs[i], psz_lang ) ||
            ( !strcasecmp( ppsz_langs[i], "any" ) && strcasecmp( psz_lang, "none") ) )
            return i;
        if( !strcasecmp( ppsz_langs[i], "none" ) )
            break;
    }

    return -1;
}