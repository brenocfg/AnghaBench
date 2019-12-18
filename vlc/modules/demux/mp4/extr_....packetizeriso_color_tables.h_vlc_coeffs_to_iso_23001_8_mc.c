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
typedef  scalar_t__ video_color_space_t ;
typedef  enum iso_23001_8_mc { ____Placeholder_iso_23001_8_mc } iso_23001_8_mc ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 int ISO_23001_8_MC_UNSPECIFIED ; 
 scalar_t__* iso_23001_8_mc_to_vlc_coeffs_table ; 

__attribute__((used)) static inline enum iso_23001_8_mc vlc_coeffs_to_iso_23001_8_mc( video_color_space_t v )
{
    for(size_t i=1; i<ARRAY_SIZE(iso_23001_8_mc_to_vlc_coeffs_table); i++)
        if(iso_23001_8_mc_to_vlc_coeffs_table[i] == v)
            return (enum iso_23001_8_mc) i;
    return ISO_23001_8_MC_UNSPECIFIED;
}