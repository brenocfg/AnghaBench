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
struct TYPE_3__ {int slice_type; int /*<<< orphan*/  dependent_slice_segment_flag; } ;
typedef  TYPE_1__ hevc_slice_segment_header_t ;
typedef  enum hevc_slice_type_e { ____Placeholder_hevc_slice_type_e } hevc_slice_type_e ;

/* Variables and functions */

bool hevc_get_slice_type( const hevc_slice_segment_header_t *p_sli, enum hevc_slice_type_e *pi_type )
{
    if( !p_sli->dependent_slice_segment_flag )
    {
        *pi_type = p_sli->slice_type;
        return true;
    }
    return false;
}