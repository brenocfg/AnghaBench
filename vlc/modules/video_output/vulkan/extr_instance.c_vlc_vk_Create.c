#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vlc_vk_t {int /*<<< orphan*/  ref_count; int /*<<< orphan*/ * module; struct vout_window_t* window; scalar_t__ surface; int /*<<< orphan*/ * instance; int /*<<< orphan*/ * ctx; } ;
typedef  struct vlc_vk_t vlc_vk_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vout_window_t {int dummy; } ;
typedef  scalar_t__ VkSurfaceKHR ;

/* Variables and functions */
 int /*<<< orphan*/ * module_need (struct vlc_vk_t*,char*,char const*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_atomic_rc_init (int /*<<< orphan*/ *) ; 
 struct vlc_vk_t* vlc_object_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_object_delete (struct vlc_vk_t*) ; 

vlc_vk_t *vlc_vk_Create(struct vout_window_t *wnd, const char *name)
{
    vlc_object_t *parent = (vlc_object_t *) wnd;
    struct vlc_vk_t *vk;

    vk = vlc_object_create(parent, sizeof (*vk));
    if (unlikely(vk == NULL))
        return NULL;

    vk->ctx = NULL;
    vk->instance = NULL;
    vk->surface = (VkSurfaceKHR) NULL;

    vk->window = wnd;
    vk->module = module_need(vk, "vulkan", name, true);
    if (vk->module == NULL)
    {
        vlc_object_delete(vk);
        return NULL;
    }
    vlc_atomic_rc_init(&vk->ref_count);

    return vk;
}