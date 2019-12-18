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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__ bit_depth_chroma_minus8; scalar_t__ chroma_format_idc; } ;
typedef  TYPE_1__ hevc_sequence_parameter_set_t ;

/* Variables and functions */

bool hevc_get_chroma_luma( const hevc_sequence_parameter_set_t *p_sps, uint8_t *pi_chroma_format,
                           uint8_t *pi_depth_luma, uint8_t *pi_depth_chroma )
{
    *pi_chroma_format = p_sps->chroma_format_idc;
    *pi_depth_luma = p_sps->bit_depth_chroma_minus8 + 8;
    *pi_depth_chroma = p_sps->bit_depth_chroma_minus8 + 8;
    return true;
}