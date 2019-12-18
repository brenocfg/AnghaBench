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
 scalar_t__ IsEndTag (char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static const char * FindNextTag( const char *psz, const char **ppsz_taglast )
{
    psz = strchr( psz, '<' );
    if( psz )
    {
        *ppsz_taglast = strchr( psz + 1, '>' );
        if( *ppsz_taglast )
        {
            const size_t tagsize = *ppsz_taglast - psz + 1;
            if( tagsize <= 3 )
            {
                if( tagsize < 2 || IsEndTag(psz) )
                    *ppsz_taglast = psz = NULL;
            }
        } else psz = NULL;
    }
    return psz;
}