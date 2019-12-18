#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int log2_min_luma_coding_block_size_minus3; unsigned int const log2_diff_max_min_luma_coding_block_size; int pic_width_in_luma_samples; int pic_height_in_luma_samples; } ;
typedef  TYPE_1__ hevc_sequence_parameter_set_t ;

/* Variables and functions */

__attribute__((used)) static bool hevc_get_picture_CtbsYsize( const hevc_sequence_parameter_set_t *p_sps, unsigned *p_w, unsigned *p_h )
{
    const unsigned int MinCbLog2SizeY = p_sps->log2_min_luma_coding_block_size_minus3 + 3;
    const unsigned int CtbLog2SizeY = MinCbLog2SizeY + p_sps->log2_diff_max_min_luma_coding_block_size;
    if( CtbLog2SizeY > 31 )
        return false;
    const unsigned int CtbSizeY = 1 << CtbLog2SizeY;
    *p_w = (p_sps->pic_width_in_luma_samples - 1) / CtbSizeY + 1;
    *p_h = (p_sps->pic_height_in_luma_samples - 1) / CtbSizeY + 1;
    return true;
}