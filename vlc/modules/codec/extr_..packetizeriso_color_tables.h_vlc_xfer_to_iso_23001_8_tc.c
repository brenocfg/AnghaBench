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
typedef  scalar_t__ video_transfer_func_t ;
typedef  enum iso_23001_8_tc { ____Placeholder_iso_23001_8_tc } iso_23001_8_tc ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 int ISO_23001_8_TC_UNSPECIFIED ; 
 scalar_t__* iso_23001_8_tc_to_vlc_xfer_table ; 

__attribute__((used)) static inline enum iso_23001_8_tc vlc_xfer_to_iso_23001_8_tc( video_transfer_func_t v )
{
    for(size_t i=1; i<ARRAY_SIZE(iso_23001_8_tc_to_vlc_xfer_table); i++)
        if(iso_23001_8_tc_to_vlc_xfer_table[i] == v)
            return (enum iso_23001_8_tc) i;
    return ISO_23001_8_TC_UNSPECIFIED;
}