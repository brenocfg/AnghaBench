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
struct render_context {int /*<<< orphan*/ * libvlc_d3d; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DDevice9_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Cleanup_cb( void *opaque )
{
    /* here we can release all things Direct3D9 for good  (if playing only one file) */
    struct render_context *ctx = opaque;
    if (ctx->libvlc_d3d)
    {
        IDirect3DDevice9_Release(ctx->libvlc_d3d);
        ctx->libvlc_d3d = NULL;
    }
}