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
struct TYPE_3__ {int /*<<< orphan*/  drm_fd; int /*<<< orphan*/ * fb; int /*<<< orphan*/  size; int /*<<< orphan*/ * map; int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ vout_display_sys_t ;
typedef  size_t uint32_t ;
struct drm_mode_destroy_dumb {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_IOCTL_MODE_DESTROY_DUMB ; 
 int /*<<< orphan*/  drmIoctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_mode_destroy_dumb*) ; 
 int /*<<< orphan*/  drmModeRmFB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DestroyFB(vout_display_sys_t const *sys, uint32_t const buf)
{
    struct drm_mode_destroy_dumb destroy_req = { .handle = sys->handle[buf] };

    munmap(sys->map[buf], sys->size);
    drmModeRmFB(sys->drm_fd, sys->fb[buf]);
    drmIoctl(sys->drm_fd, DRM_IOCTL_MODE_DESTROY_DUMB, &destroy_req);
}