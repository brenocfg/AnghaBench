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
typedef  int /*<<< orphan*/  video_color_space_t ;
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COLOR_SPACE_UNDEF ; 
 int /*<<< orphan*/ * iso_23001_8_mc_to_vlc_coeffs_table ; 

__attribute__((used)) static inline video_color_space_t iso_23001_8_mc_to_vlc_coeffs( uint8_t v )
{
    return v < ARRAY_SIZE(iso_23001_8_mc_to_vlc_coeffs_table)
           ? iso_23001_8_mc_to_vlc_coeffs_table[v]
           : COLOR_SPACE_UNDEF;
}