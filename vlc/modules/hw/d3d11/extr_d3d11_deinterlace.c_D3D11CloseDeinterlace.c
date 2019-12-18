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
struct TYPE_5__ {int /*<<< orphan*/  hd3d; int /*<<< orphan*/  d3d_dev; int /*<<< orphan*/  d3d_proc; int /*<<< orphan*/  outTexture; int /*<<< orphan*/  processorOutput; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D11_FilterReleaseInstance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D11_ReleaseProcessor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D11Texture2D_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11VideoProcessorOutputView_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

void D3D11CloseDeinterlace(vlc_object_t *obj)
{
    filter_t *filter = (filter_t *)obj;
    filter_sys_t *sys = filter->p_sys;

    if (likely(sys->processorOutput))
        ID3D11VideoProcessorOutputView_Release(sys->processorOutput);
    ID3D11Texture2D_Release(sys->outTexture);
    D3D11_ReleaseProcessor( &sys->d3d_proc );
    D3D11_FilterReleaseInstance(&sys->d3d_dev);
    D3D11_Destroy(&sys->hd3d);

    free(sys);
}