#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_6__ {int /*<<< orphan*/ * d3dregion; scalar_t__ d3dregion_count; int /*<<< orphan*/ * sceneTexture; int /*<<< orphan*/ * sceneVertexBuffer; } ;
typedef  TYPE_2__ vout_display_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Direct3D9DeleteRegions (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DTexture9_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DVertexBuffer9_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 

__attribute__((used)) static void Direct3D9DestroyScene(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;

    Direct3D9DeleteRegions(sys->d3dregion_count, sys->d3dregion);

    if (sys->sceneVertexBuffer)
    {
        IDirect3DVertexBuffer9_Release(sys->sceneVertexBuffer);
        sys->sceneVertexBuffer = NULL;
    }

    if (sys->sceneTexture)
    {
        IDirect3DTexture9_Release(sys->sceneTexture);
        sys->sceneTexture = NULL;
    }

    sys->d3dregion_count = 0;
    sys->d3dregion       = NULL;

    msg_Dbg(vd, "Direct3D9 scene released successfully");
}