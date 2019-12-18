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
 scalar_t__ isalnum (char const) ; 
 scalar_t__ isalpha (char const) ; 
 scalar_t__ isspace (char const) ; 

__attribute__((used)) static const char *SplitTag( const char *psz_tag, size_t *pi_tag, const char **ppsz_attrs )
{
    psz_tag += IsEndTag( psz_tag ) ? 2 : 1;
    const char *p = psz_tag;
    *pi_tag = 0;
    if( isalpha( *p ) )
    {
        while( isalnum( *p ) )
        {
            p++;
            (*pi_tag)++;
        }
        while( isspace( *p ) )
            p++;
    }
    *ppsz_attrs = p;
    return psz_tag;
}