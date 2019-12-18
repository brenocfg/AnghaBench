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
 scalar_t__ DTS_SYNC_NONE ; 
 scalar_t__ dts_header_getSyncword (void const*) ; 

bool vlc_dts_header_IsSync( const void *p_buf, size_t i_buf )
{
    return i_buf >= 6
        && dts_header_getSyncword( p_buf ) != DTS_SYNC_NONE;
}