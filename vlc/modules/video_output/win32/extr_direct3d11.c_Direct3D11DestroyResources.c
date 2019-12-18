#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_7__ {int /*<<< orphan*/ * prepareWait; int /*<<< orphan*/  regionQuad; int /*<<< orphan*/  projectionVShader; int /*<<< orphan*/  flatVShader; int /*<<< orphan*/  stagingSys; scalar_t__ d3dregion_count; int /*<<< orphan*/  d3dregions; int /*<<< orphan*/  picQuad; } ;
typedef  TYPE_2__ vout_display_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_ReleasePixelShader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D11_ReleaseQuad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D11_ReleaseVertexShader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Direct3D11DeleteRegions (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Direct3D11DestroyPool (TYPE_1__*) ; 
 int /*<<< orphan*/  ID3D11Query_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseD3D11PictureSys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 

__attribute__((used)) static void Direct3D11DestroyResources(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;

    Direct3D11DestroyPool(vd);

    D3D11_ReleaseQuad(&sys->picQuad);
    Direct3D11DeleteRegions(sys->d3dregion_count, sys->d3dregions);
    sys->d3dregion_count = 0;

    ReleaseD3D11PictureSys(&sys->stagingSys);

    D3D11_ReleaseVertexShader(&sys->flatVShader);
    D3D11_ReleaseVertexShader(&sys->projectionVShader);

    D3D11_ReleasePixelShader(&sys->regionQuad);
    if (sys->prepareWait)
    {
        ID3D11Query_Release(sys->prepareWait);
        sys->prepareWait = NULL;
    }

    msg_Dbg(vd, "Direct3D11 resources destroyed");
}