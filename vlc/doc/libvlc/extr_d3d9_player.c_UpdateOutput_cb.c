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
struct render_context {int dummy; } ;
typedef  int /*<<< orphan*/  libvlc_video_output_cfg_t ;
struct TYPE_3__ {scalar_t__ device; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ libvlc_video_direct3d_cfg_t ;
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;

/* Variables and functions */
 int Resize (struct render_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool UpdateOutput_cb( void *opaque, const libvlc_video_direct3d_cfg_t *cfg, libvlc_video_output_cfg_t *out )
{
    struct render_context *ctx = opaque;
    return Resize(ctx, cfg->width, cfg->height, (IDirect3DDevice9*)cfg->device, out);
}