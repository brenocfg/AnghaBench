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
 scalar_t__* LIBDIR ; 
 scalar_t__* SYSDATADIR ; 

__attribute__((used)) static const char *config_GetRelDir( const char *dir )
{
    static int prefixlen = -1;

    if( prefixlen == -1 )
    {
        prefixlen = 0;
        while( LIBDIR[ prefixlen ] && SYSDATADIR[ prefixlen ]
               && LIBDIR[ prefixlen ] == SYSDATADIR[ prefixlen])
            prefixlen++;
    }

    return dir + prefixlen;
}