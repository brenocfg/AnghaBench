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
typedef  unsigned int uint64_t ;
typedef  enum j2k_profiles_e { ____Placeholder_j2k_profiles_e } j2k_profiles_e ;

/* Variables and functions */
 int J2K_PROFILE_3G ; 
 int J2K_PROFILE_HD ; 
 int J2K_PROFILE_SD ; 

__attribute__((used)) static inline enum j2k_profiles_e j2k_get_profile( unsigned w, unsigned h,
                                                   unsigned num, unsigned den, bool p )
{
    const uint64_t s = w *(uint64_t)h;
    const uint64_t f = num / den;
    if( s <= 720*576 && f < 50 )
        return J2K_PROFILE_SD; /* VSF_TR-01_2013-04-15 */
    else if( s <= 1280*720 && f < 60 && p )
        return J2K_PROFILE_HD;
    else if( s <= 1920*1080 && f < 60 && !p )
        return J2K_PROFILE_HD;
    else
        return J2K_PROFILE_3G;
}