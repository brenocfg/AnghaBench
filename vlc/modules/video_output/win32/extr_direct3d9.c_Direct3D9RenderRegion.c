#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_8__ {int /*<<< orphan*/ * dev; } ;
struct TYPE_10__ {int /*<<< orphan*/ * d3dx_shader; int /*<<< orphan*/  sceneVertexBuffer; TYPE_1__ d3d_dev; } ;
typedef  TYPE_3__ vout_display_sys_t ;
struct TYPE_11__ {float width; float height; scalar_t__ texture; int /*<<< orphan*/  vertex; } ;
typedef  TYPE_4__ d3d_region_t ;
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;
typedef  int /*<<< orphan*/  IDirect3DBaseTexture9 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CUSTOMVERTEX ;

/* Variables and functions */
 int /*<<< orphan*/  D3DLOCK_DISCARD ; 
 int /*<<< orphan*/  D3DPT_TRIANGLEFAN ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_DrawPrimitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetPixelShader (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetPixelShaderConstantF (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*,int) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetStreamSource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetTexture (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DVertexBuffer9_Lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DVertexBuffer9_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Direct3D9RenderRegion(vout_display_t *vd,
                                const d3d_region_t *region,
                                bool use_pixel_shader)
{
    vout_display_sys_t *sys = vd->sys;

    IDirect3DDevice9 *d3ddev = vd->sys->d3d_dev.dev;

    HRESULT hr;

    /* Import vertices */
    void *vertex;
    hr = IDirect3DVertexBuffer9_Lock(sys->sceneVertexBuffer, 0, 0, &vertex, D3DLOCK_DISCARD);
    if (FAILED(hr)) {
        msg_Dbg(vd, "Failed IDirect3DVertexBuffer9_Lock: 0x%lX", hr);
        return -1;
    }
    memcpy(vertex, region->vertex, sizeof(region->vertex));
    hr = IDirect3DVertexBuffer9_Unlock(sys->sceneVertexBuffer);
    if (FAILED(hr)) {
        msg_Dbg(vd, "Failed IDirect3DVertexBuffer9_Unlock: 0x%lX", hr);
        return -1;
    }

    // Render the vertex buffer contents
    hr = IDirect3DDevice9_SetStreamSource(d3ddev, 0, sys->sceneVertexBuffer, 0, sizeof(CUSTOMVERTEX));
    if (FAILED(hr)) {
        msg_Dbg(vd, "Failed SetStreamSource: 0x%lX", hr);
        return -1;
    }

    // Setup our texture. Using textures introduces the texture stage states,
    // which govern how textures get blended together (in the case of multiple
    // textures) and lighting information. In this case, we are modulating
    // (blending) our texture with the diffuse color of the vertices.
    hr = IDirect3DDevice9_SetTexture(d3ddev, 0, (IDirect3DBaseTexture9*)region->texture);
    if (FAILED(hr)) {
        msg_Dbg(vd, "Failed SetTexture: 0x%lX", hr);
        return -1;
    }

    if (sys->d3dx_shader) {
        if (use_pixel_shader)
        {
            hr = IDirect3DDevice9_SetPixelShader(d3ddev, sys->d3dx_shader);
            float shader_data[4] = { region->width, region->height, 0, 0 };
            hr = IDirect3DDevice9_SetPixelShaderConstantF(d3ddev, 0, shader_data, 1);
            if (FAILED(hr)) {
                msg_Dbg(vd, "Failed SetPixelShaderConstantF: 0x%lX", hr);
                return -1;
            }
        }
        else /* Disable any existing pixel shader. */
            hr = IDirect3DDevice9_SetPixelShader(d3ddev, NULL);
        if (FAILED(hr)) {
            msg_Dbg(vd, "Failed SetPixelShader: 0x%lX", hr);
            return -1;
        }
    }

    // draw rectangle
    hr = IDirect3DDevice9_DrawPrimitive(d3ddev, D3DPT_TRIANGLEFAN, 0, 2);
    if (FAILED(hr)) {
        msg_Dbg(vd, "Failed DrawPrimitive: 0x%lX", hr);
        return -1;
    }
    return 0;
}