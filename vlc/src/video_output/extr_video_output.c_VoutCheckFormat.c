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
struct TYPE_3__ {int i_width; int i_height; scalar_t__ i_sar_num; scalar_t__ i_sar_den; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */

__attribute__((used)) static bool VoutCheckFormat(const video_format_t *src)
{
    if (src->i_width == 0  || src->i_width  > 8192 ||
        src->i_height == 0 || src->i_height > 8192)
        return false;
    if (src->i_sar_num <= 0 || src->i_sar_den <= 0)
        return false;
    return true;
}