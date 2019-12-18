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
 int /*<<< orphan*/  INPUT_DURATION_UNSET ; 
 int sscanf (char const*,char*,int*,int*,int*) ; 
 int /*<<< orphan*/  vlc_tick_from_sec (int) ; 

__attribute__((used)) static vlc_tick_t strTimeToMTime( const char *psz )
{
    int h, m, s;
    switch( sscanf( psz, "%u:%u:%u", &h, &m, &s ) )
    {
    case 3:
        return vlc_tick_from_sec( ( h*60 + m )*60 + s );
    case 2:
        return vlc_tick_from_sec( h*60 + m );
    default:
        return INPUT_DURATION_UNSET;
    }
}