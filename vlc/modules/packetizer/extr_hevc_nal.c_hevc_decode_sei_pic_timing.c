#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ frame_field_info_present_flag; } ;
struct TYPE_8__ {TYPE_1__ vui; } ;
typedef  TYPE_2__ hevc_sequence_parameter_set_t ;
struct TYPE_9__ {int source_scan_type; void* pic_struct; } ;
typedef  TYPE_3__ hevc_sei_pic_timing_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 void* bs_read (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* malloc (int) ; 

hevc_sei_pic_timing_t * hevc_decode_sei_pic_timing( bs_t *p_bs,
                                                    const hevc_sequence_parameter_set_t *p_sps )
{
    hevc_sei_pic_timing_t *p_timing = malloc(sizeof(*p_timing));
    if( p_timing )
    {
        if( p_sps->vui.frame_field_info_present_flag )
        {
            p_timing->pic_struct = bs_read( p_bs, 4 );
            p_timing->source_scan_type = bs_read( p_bs, 2 );
        }
        else
        {
            p_timing->pic_struct = 0;
            p_timing->source_scan_type = 1;
        }
    }
    return p_timing;
}