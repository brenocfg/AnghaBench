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
struct TYPE_3__ {scalar_t__ i_sar_num; int i_sar_den; int i_visible_width; } ;
typedef  TYPE_1__ video_format_t ;
typedef  int int64_t ;

/* Variables and functions */

__attribute__((used)) static unsigned ApplyARtoWidth(const video_format_t *vfmt)
{
    if (vfmt->i_sar_num > 0 && vfmt->i_sar_den > 0)
    {
        return (int64_t)vfmt->i_sar_num *
               (int64_t)vfmt->i_visible_width / vfmt->i_sar_den;
    }
    else return vfmt->i_visible_width;
}