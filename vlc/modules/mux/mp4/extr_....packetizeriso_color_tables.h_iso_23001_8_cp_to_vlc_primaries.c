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
typedef  int /*<<< orphan*/  video_color_primaries_t ;
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COLOR_PRIMARIES_EBU_3213 ; 
 int /*<<< orphan*/  COLOR_PRIMARIES_UNDEF ; 
 size_t ISO_23001_8_CP_EBU_3213 ; 
 int /*<<< orphan*/ * iso_23001_8_cp_to_vlc_primaries_table ; 

__attribute__((used)) static inline video_color_primaries_t iso_23001_8_cp_to_vlc_primaries( uint8_t v )
{
    if( v == ISO_23001_8_CP_EBU_3213 )
        return COLOR_PRIMARIES_EBU_3213;
    return v < ARRAY_SIZE(iso_23001_8_cp_to_vlc_primaries_table)
           ? iso_23001_8_cp_to_vlc_primaries_table[v]
           : COLOR_PRIMARIES_UNDEF;
}