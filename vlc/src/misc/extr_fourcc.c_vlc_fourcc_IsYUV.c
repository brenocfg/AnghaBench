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
typedef  scalar_t__ vlc_fourcc_t ;

/* Variables and functions */
 scalar_t__* p_list_YUV ; 

bool vlc_fourcc_IsYUV(vlc_fourcc_t fcc)
{
    for( unsigned i = 0; p_list_YUV[i]; i++ )
    {
        if( p_list_YUV[i] == fcc )
            return true;
    }
    return false;
}