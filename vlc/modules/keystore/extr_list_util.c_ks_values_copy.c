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
 unsigned int KEY_MAX ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 char* strdup (char const* const) ; 

int
ks_values_copy(const char * ppsz_dst[KEY_MAX],
               const char *const ppsz_src[KEY_MAX])
{
    for (unsigned int i = 0; i < KEY_MAX; ++i)
    {
        if (ppsz_src[i])
        {
            ppsz_dst[i] = strdup(ppsz_src[i]);
            if (!ppsz_dst[i])
                return VLC_EGENERIC;
        }
    }
    return VLC_SUCCESS;
}