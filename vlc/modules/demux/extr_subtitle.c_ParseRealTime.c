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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ VLC_EGENERIC ; 
 scalar_t__ VLC_TICK_FROM_MS (int) ; 
 int sscanf (char*,char*,int*,...) ; 
 scalar_t__ vlc_tick_from_sec (int) ; 

__attribute__((used)) static int64_t ParseRealTime( char *psz, int *h, int *m, int *s, int *f )
{
    if( *psz == '\0' ) return 0;
    if( sscanf( psz, "%d:%d:%d.%d", h, m, s, f ) == 4 ||
            sscanf( psz, "%d:%d.%d", m, s, f ) == 3 ||
            sscanf( psz, "%d.%d", s, f ) == 2 ||
            sscanf( psz, "%d:%d", m, s ) == 2 ||
            sscanf( psz, "%d", s ) == 1 )
    {
        return vlc_tick_from_sec((( *h * 60 + *m ) * 60 ) + *s )
               + VLC_TICK_FROM_MS(*f * 10);
    }
    else return VLC_EGENERIC;
}