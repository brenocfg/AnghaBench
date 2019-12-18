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
 scalar_t__ isspace (unsigned char) ; 

__attribute__((used)) static int skip_space( char **psz_command )
{
    char *psz_temp = *psz_command;

    while( isspace( (unsigned char)*psz_temp ) )
    {
        ++psz_temp;
    }
    if( psz_temp == *psz_command )
    {
        return VLC_EGENERIC;
    }
    *psz_command = psz_temp;
    return VLC_SUCCESS;
}