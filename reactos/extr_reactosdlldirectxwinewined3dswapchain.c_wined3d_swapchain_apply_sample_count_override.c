#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wined3d_swapchain {TYPE_2__* device; } ;
struct TYPE_5__ {int /*<<< orphan*/  samples; } ;
struct wined3d_gl_info {TYPE_1__ limits; } ;
struct wined3d_format {unsigned int multisample_types; } ;
typedef  enum wined3d_multisample_type { ____Placeholder_wined3d_multisample_type } wined3d_multisample_type ;
typedef  enum wined3d_format_id { ____Placeholder_wined3d_format_id } wined3d_format_id ;
struct TYPE_8__ {unsigned int sample_count; } ;
struct TYPE_7__ {struct wined3d_gl_info gl_info; } ;
struct TYPE_6__ {TYPE_3__* adapter; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/  WINED3DUSAGE_RENDERTARGET ; 
 int min (unsigned int,int /*<<< orphan*/ ) ; 
 struct wined3d_format* wined3d_get_format (struct wined3d_gl_info const*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__ wined3d_settings ; 

__attribute__((used)) static void wined3d_swapchain_apply_sample_count_override(const struct wined3d_swapchain *swapchain,
        enum wined3d_format_id format_id, enum wined3d_multisample_type *type, DWORD *quality)
{
    const struct wined3d_gl_info *gl_info;
    const struct wined3d_format *format;
    enum wined3d_multisample_type t;

    if (wined3d_settings.sample_count == ~0u)
        return;

    gl_info = &swapchain->device->adapter->gl_info;
    if (!(format = wined3d_get_format(gl_info, format_id, WINED3DUSAGE_RENDERTARGET)))
        return;

    if ((t = min(wined3d_settings.sample_count, gl_info->limits.samples)))
        while (!(format->multisample_types & 1u << (t - 1)))
            ++t;
    TRACE("Using sample count %u.\n", t);
    *type = t;
    *quality = 0;
}