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
struct render_context {int /*<<< orphan*/  libvlc_d3d; } ;
typedef  int /*<<< orphan*/  libvlc_video_direct3d_hdr10_metadata_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DDevice9_Present (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool StartRendering_cb( void *opaque, bool enter, const libvlc_video_direct3d_hdr10_metadata_t *hdr10 )
{
    struct render_context *ctx = opaque;
    if ( enter )
    {
        /* we already set the RenderTarget on the IDirect3DDevice9 */
        return true;
    }

    /* VLC has finished preparing drawning on our surface, we need do the drawing now
       so the surface is finished rendering when Swap() is called to do our own
       rendering */
    IDirect3DDevice9_Present(ctx->libvlc_d3d, NULL, NULL, NULL, NULL);
    return true;
}