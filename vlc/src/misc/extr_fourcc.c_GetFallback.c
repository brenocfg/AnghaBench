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
typedef  scalar_t__ const vlc_fourcc_t ;

/* Variables and functions */

__attribute__((used)) static const vlc_fourcc_t *GetFallback( vlc_fourcc_t i_fourcc,
                                        const vlc_fourcc_t *pp_fallback[],
                                        const vlc_fourcc_t p_list[] )
{
    for( unsigned i = 0; pp_fallback[i]; i++ )
    {
        if( pp_fallback[i][0] == i_fourcc )
            return pp_fallback[i];
    }
    return p_list;
}