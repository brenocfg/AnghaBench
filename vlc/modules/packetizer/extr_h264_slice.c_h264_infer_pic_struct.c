#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {int i_bottom_field_flag; scalar_t__ i_field_pic_flag; } ;
typedef  TYPE_2__ h264_slice_t ;
struct TYPE_6__ {int /*<<< orphan*/  b_pic_struct_present_flag; } ;
struct TYPE_8__ {TYPE_1__ vui; } ;
typedef  TYPE_3__ h264_sequence_parameter_set_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t h264_infer_pic_struct( const h264_sequence_parameter_set_t *p_sps,
                                      const h264_slice_t *p_slice,
                                      uint8_t i_pic_struct, int tFOC, int bFOC )
{
    /* See D-1 and note 6 */
    if( !p_sps->vui.b_pic_struct_present_flag || i_pic_struct >= 9 )
    {
        if( p_slice->i_field_pic_flag )
            i_pic_struct = 1 + p_slice->i_bottom_field_flag;
        else if( tFOC == bFOC )
            i_pic_struct = 0;
        else if( tFOC < bFOC )
            i_pic_struct = 3;
        else
            i_pic_struct = 4;
    }

    return i_pic_struct;
}