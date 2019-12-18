#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_11__ {int /*<<< orphan*/ * dev; } ;
struct TYPE_13__ {int clear_scene; int /*<<< orphan*/  outside_opaque; int /*<<< orphan*/  (* startEndRenderingCb ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;TYPE_1__ d3d_dev; } ;
typedef  TYPE_3__ vout_display_sys_t ;
struct TYPE_14__ {scalar_t__ texture; } ;
typedef  TYPE_4__ d3d_region_t ;
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DCLEAR_TARGET ; 
 int /*<<< orphan*/  D3DCOLOR_XRGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3DRS_ALPHABLENDENABLE ; 
 int /*<<< orphan*/  Direct3D9RenderRegion (TYPE_2__*,TYPE_4__*,int) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDirect3DDevice9_BeginScene (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_Clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_EndScene (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DDevice9_SetRenderState (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Direct3D9RenderScene(vout_display_t *vd,
                                d3d_region_t *picture,
                                size_t subpicture_count,
                                d3d_region_t *subpicture)
{
    vout_display_sys_t *sys = vd->sys;
    IDirect3DDevice9 *d3ddev = sys->d3d_dev.dev;
    HRESULT hr;

    if (sys->startEndRenderingCb && !sys->startEndRenderingCb( sys->outside_opaque, true, NULL ))
        return;

    if (sys->clear_scene) {
        /* Clear the backbuffer and the zbuffer */
        hr = IDirect3DDevice9_Clear(d3ddev, 0, NULL, D3DCLEAR_TARGET,
                                  D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
        if (FAILED(hr)) {
            msg_Dbg(vd, "Failed Clear: 0x%lX", hr);
            return;
        }
        sys->clear_scene = false;
    }

    hr = IDirect3DDevice9_BeginScene(d3ddev);
    if (FAILED(hr)) {
        msg_Dbg(vd, "Failed BeginScene: 0x%lX", hr);
        return;
    }

    Direct3D9RenderRegion(vd, picture, true);

    if (subpicture_count)
    {
        IDirect3DDevice9_SetRenderState(d3ddev, D3DRS_ALPHABLENDENABLE, TRUE);
        for (size_t i = 0; i < subpicture_count; i++) {
            d3d_region_t *r = &subpicture[i];
            if (r->texture)
                Direct3D9RenderRegion(vd, r, false);
        }
        IDirect3DDevice9_SetRenderState(d3ddev, D3DRS_ALPHABLENDENABLE, FALSE);
    }

    hr = IDirect3DDevice9_EndScene(d3ddev);
    if (FAILED(hr))
        msg_Dbg(vd, "Failed EndScene: 0x%lX", hr);

    if (sys->startEndRenderingCb)
        sys->startEndRenderingCb( sys->outside_opaque, false, NULL );
}