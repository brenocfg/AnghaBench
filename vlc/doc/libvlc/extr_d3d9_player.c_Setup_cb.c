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
struct render_context {int /*<<< orphan*/  d3d; } ;
struct TYPE_3__ {int /*<<< orphan*/  adapter; int /*<<< orphan*/  device_context; } ;
typedef  TYPE_1__ libvlc_video_direct3d_device_setup_t ;
typedef  int /*<<< orphan*/  libvlc_video_direct3d_device_cfg_t ;

/* Variables and functions */
 int /*<<< orphan*/  D3DADAPTER_DEFAULT ; 

__attribute__((used)) static bool Setup_cb( void **opaque, const libvlc_video_direct3d_device_cfg_t *cfg, libvlc_video_direct3d_device_setup_t *out )
{
    struct render_context *ctx = *opaque;
    out->device_context = ctx->d3d;
    out->adapter = D3DADAPTER_DEFAULT;
    return true;
}