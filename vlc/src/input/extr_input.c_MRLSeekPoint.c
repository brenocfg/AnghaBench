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
 scalar_t__ INT_MAX ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *MRLSeekPoint( const char *str, int *title, int *chapter )
{
    char *end;
    unsigned long u;

    /* Look for the title */
    u = strtoul( str, &end, 0 );
    *title = (str == end || u > (unsigned long)INT_MAX) ? -1 : (int)u;
    str = end;

    /* Look for the chapter */
    if( *str == ':' )
    {
        str++;
        u = strtoul( str, &end, 0 );
        *chapter = (str == end || u > (unsigned long)INT_MAX) ? -1 : (int)u;
        str = end;
    }
    else
        *chapter = -1;

    return str;
}