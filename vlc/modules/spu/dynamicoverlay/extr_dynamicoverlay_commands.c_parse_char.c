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
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static int parse_char( char **psz_command, char **psz_end,
                       int count, char *psz_value )
{
    if( *psz_end - *psz_command < count )
    {
        return VLC_EGENERIC;
    }
    memcpy( psz_value, *psz_command, count );
    *psz_command += count;
    return VLC_SUCCESS;
}