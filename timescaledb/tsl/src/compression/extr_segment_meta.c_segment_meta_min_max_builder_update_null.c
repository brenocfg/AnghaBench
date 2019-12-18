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
struct TYPE_3__ {int has_null; } ;
typedef  TYPE_1__ SegmentMetaMinMaxBuilder ;

/* Variables and functions */

void
segment_meta_min_max_builder_update_null(SegmentMetaMinMaxBuilder *builder)
{
	builder->has_null = true;
}