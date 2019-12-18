#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_5__ {int /*<<< orphan*/  d3d9_dll; int /*<<< orphan*/  hdecoder_dll; int /*<<< orphan*/  d3d_dev; int /*<<< orphan*/  processor; int /*<<< orphan*/  hw_surface; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  D3D9_FilterReleaseInstance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DSurface9_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectXVideoProcessor_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void D3D9CloseAdjust(vlc_object_t *obj)
{
    filter_t *filter = (filter_t *)obj;
    filter_sys_t *sys = filter->p_sys;

    IDirect3DSurface9_Release( sys->hw_surface );
    IDirectXVideoProcessor_Release( sys->processor );
    D3D9_FilterReleaseInstance( &sys->d3d_dev );
    FreeLibrary( sys->hdecoder_dll );
    FreeLibrary( sys->d3d9_dll );

    free(sys);
}