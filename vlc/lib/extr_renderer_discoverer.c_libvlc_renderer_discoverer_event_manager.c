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
struct TYPE_3__ {int /*<<< orphan*/  event_manager; } ;
typedef  TYPE_1__ libvlc_renderer_discoverer_t ;
typedef  int /*<<< orphan*/  libvlc_event_manager_t ;

/* Variables and functions */

libvlc_event_manager_t *
libvlc_renderer_discoverer_event_manager( libvlc_renderer_discoverer_t *p_lrd )
{
    return &p_lrd->event_manager;
}