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
struct device_state {unsigned int num_render_targets; int /*<<< orphan*/  viewport; int /*<<< orphan*/ * depth_stencil; int /*<<< orphan*/ ** render_targets; } ;
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DDevice9_SetDepthStencilSurface (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetRenderTarget (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetViewport (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DSurface9_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void device_state_restore(IDirect3DDevice9 *device, struct device_state *state)
{
    unsigned int i;

    for (i = 0; i < state->num_render_targets; i++)
    {
        IDirect3DDevice9_SetRenderTarget(device, i, state->render_targets[i]);
        if (state->render_targets[i])
            IDirect3DSurface9_Release(state->render_targets[i]);
        state->render_targets[i] = NULL;
    }

    IDirect3DDevice9_SetDepthStencilSurface(device, state->depth_stencil);
    if (state->depth_stencil)
    {
        IDirect3DSurface9_Release(state->depth_stencil);
        state->depth_stencil = NULL;
    }

    IDirect3DDevice9_SetViewport(device, &state->viewport);
}