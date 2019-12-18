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
struct TYPE_3__ {int /*<<< orphan*/ * p_sd; } ;
typedef  TYPE_1__ libvlc_media_discoverer_t ;

/* Variables and functions */

bool libvlc_media_discoverer_is_running(libvlc_media_discoverer_t * p_mdis)
{
    return p_mdis->p_sd != NULL;
}