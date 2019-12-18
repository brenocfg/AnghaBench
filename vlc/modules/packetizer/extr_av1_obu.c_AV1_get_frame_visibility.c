#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int show_frame; } ;
struct TYPE_5__ {TYPE_1__ header; } ;
typedef  TYPE_2__ av1_OBU_frame_header_t ;

/* Variables and functions */

bool AV1_get_frame_visibility(const av1_OBU_frame_header_t *p_fh)
{
    return p_fh->header.show_frame;
}