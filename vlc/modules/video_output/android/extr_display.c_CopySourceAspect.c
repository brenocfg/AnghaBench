#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  i_sar_den; int /*<<< orphan*/  i_sar_num; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */

__attribute__((used)) static void CopySourceAspect(video_format_t *p_dest,
                             const video_format_t *p_src)
{
    p_dest->i_sar_num = p_src->i_sar_num;
    p_dest->i_sar_den = p_src->i_sar_den;
}