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
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_3__ {int /*<<< orphan*/ * platform_sys; } ;
typedef  TYPE_1__ vlc_vk_t ;

/* Variables and functions */
 int /*<<< orphan*/  xcb_disconnect (int /*<<< orphan*/ *) ; 

void vlc_vk_ClosePlatform(vlc_vk_t *vk)
{
    xcb_connection_t *conn = vk->platform_sys;

    xcb_disconnect(conn);
}