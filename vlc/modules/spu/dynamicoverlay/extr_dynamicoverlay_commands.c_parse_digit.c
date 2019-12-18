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
typedef  long int32_t ;

/* Variables and functions */
 long INT32_MAX ; 
 long INT32_MIN ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static int parse_digit( char **psz_command, int32_t *value )
{
    char *psz_temp;
    long l = strtol( *psz_command, &psz_temp, 10 );

    if( psz_temp == *psz_command )
    {
        return VLC_EGENERIC;
    }
#if LONG_MAX > INT32_MAX
    if( l > INT32_MAX || l < INT32_MIN )
        return VLC_EGENERIC;
#endif
    *value = l;
    *psz_command = psz_temp;
    return VLC_SUCCESS;
}