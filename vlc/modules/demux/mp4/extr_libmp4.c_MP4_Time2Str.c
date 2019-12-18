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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int stime_t ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static char * MP4_Time2Str( stime_t i_duration, uint32_t i_scale )
{
    uint64_t i_time = (i_scale > 0) ? i_duration / i_scale : 0;
    unsigned h = ( i_time /( 60*60 ) ) % 60;
    unsigned m = ( i_time / 60 ) % 60;
    unsigned s = i_time % 60;
    unsigned ms = (i_scale) ? (1000*i_duration / i_scale) % 1000 : 0;

    char *out;
    if( asprintf( &out, "%u:%.2u:%.2u:%.3u", h, m, s, ms ) < 0 )
        return NULL;
    return out;
}