#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ctx; TYPE_3__* instance; int /*<<< orphan*/  vulkan; int /*<<< orphan*/  surface; int /*<<< orphan*/  swapchain; } ;
typedef  TYPE_1__ vlc_vk_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  pl_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pl_swapchain_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pl_vk_inst_destroy (TYPE_3__**) ; 
 int /*<<< orphan*/  pl_vulkan_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroySurfaceKHR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vk_ClosePlatform (TYPE_1__*) ; 

__attribute__((used)) static void Close (vlc_object_t *obj)
{
    vlc_vk_t *vk = (vlc_vk_t *) obj;

    pl_swapchain_destroy(&vk->swapchain);
    vkDestroySurfaceKHR(vk->instance->instance, vk->surface, NULL);
    pl_vulkan_destroy(&vk->vulkan);
    pl_vk_inst_destroy(&vk->instance);
    pl_context_destroy(&vk->ctx);
    vlc_vk_ClosePlatform(vk);
}