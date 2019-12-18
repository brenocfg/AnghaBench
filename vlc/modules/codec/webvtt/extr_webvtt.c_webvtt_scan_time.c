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
typedef  int /*<<< orphan*/  vlc_tick_t ;

/* Variables and functions */
 int /*<<< orphan*/  MakeTime (unsigned int*) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*,...) ; 

bool webvtt_scan_time( const char *psz, vlc_tick_t *p_time )
{
    unsigned t[4];
    if( sscanf( psz, "%2u:%2u.%3u",
                      &t[1], &t[2], &t[3] ) == 3 )
    {
        t[0] = 0;
        *p_time = MakeTime( t );
        return true;
    }
    else if( sscanf( psz, "%u:%2u:%2u.%3u",
                          &t[0], &t[1], &t[2], &t[3] ) == 4 )
    {
        *p_time = MakeTime( t );
        return true;
    }
    else return false;
}