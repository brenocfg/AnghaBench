#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_7__ {TYPE_1__* vk; } ;
typedef  TYPE_3__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_5__ {int /*<<< orphan*/  swapchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pl_swapchain_swap_buffers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PictureDisplay(vout_display_t *vd, picture_t *pic)
{
    VLC_UNUSED(pic);
    vout_display_sys_t *sys = vd->sys;
    pl_swapchain_swap_buffers(sys->vk->swapchain);
}