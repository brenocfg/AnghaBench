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
typedef  int uint8_t ;
struct TYPE_3__ {int flags; scalar_t__ op; void* y; void* x; void* height; void* width; } ;
typedef  TYPE_1__ Jbig2RegionSegmentInfo ;
typedef  scalar_t__ Jbig2ComposeOp ;

/* Variables and functions */
 void* jbig2_get_uint32 (int const*) ; 

void
jbig2_get_region_segment_info(Jbig2RegionSegmentInfo *info, const uint8_t *segment_data)
{
    /* 7.4.1 */
    info->width = jbig2_get_uint32(segment_data);
    info->height = jbig2_get_uint32(segment_data + 4);
    info->x = jbig2_get_uint32(segment_data + 8);
    info->y = jbig2_get_uint32(segment_data + 12);
    info->flags = segment_data[16];
    info->op = (Jbig2ComposeOp)(info->flags & 0x7);
}