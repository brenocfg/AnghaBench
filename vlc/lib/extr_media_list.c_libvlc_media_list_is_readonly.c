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
struct TYPE_3__ {int b_read_only; } ;
typedef  TYPE_1__ libvlc_media_list_t ;

/* Variables and functions */

bool libvlc_media_list_is_readonly( libvlc_media_list_t * p_mlist )
{
    return p_mlist->b_read_only;
}