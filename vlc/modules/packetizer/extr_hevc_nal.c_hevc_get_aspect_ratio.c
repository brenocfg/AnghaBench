#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8_t ;
struct TYPE_5__ {int aspect_ratio_idc; unsigned int sar_width; unsigned int sar_height; } ;
struct TYPE_6__ {TYPE_1__ ar; } ;
struct TYPE_7__ {TYPE_2__ vui; scalar_t__ vui_parameters_present_flag; } ;
typedef  TYPE_3__ hevc_sequence_parameter_set_t ;

/* Variables and functions */

bool hevc_get_aspect_ratio( const hevc_sequence_parameter_set_t *p_sps,
                            unsigned *num, unsigned *den )
{
    if( p_sps->vui_parameters_present_flag )
    {
        if( p_sps->vui.ar.aspect_ratio_idc != 255 )
        {
            static const uint8_t ar_table[16][2] =
            {
                {    1,      1 },
                {   12,     11 },
                {   10,     11 },
                {   16,     11 },
                {   40,     33 },
                {   24,     11 },
                {   20,     11 },
                {   32,     11 },
                {   80,     33 },
                {   18,     11 },
                {   15,     11 },
                {   64,     33 },
                {  160,     99 },
                {    4,      3 },
                {    3,      2 },
                {    2,      1 },
            };
            if( p_sps->vui.ar.aspect_ratio_idc > 0 &&
                p_sps->vui.ar.aspect_ratio_idc < 17 )
            {
                *num = ar_table[p_sps->vui.ar.aspect_ratio_idc - 1][0];
                *den = ar_table[p_sps->vui.ar.aspect_ratio_idc - 1][1];
                return true;
            }
        }
        else
        {
            *num = p_sps->vui.ar.sar_width;
            *den = p_sps->vui.ar.sar_height;
            return true;
        }
    }
    return false;
}