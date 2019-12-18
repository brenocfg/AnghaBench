#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* sys; } ;
typedef  TYPE_3__ vlc_va_t ;
struct TYPE_8__ {void* video_context; } ;
struct TYPE_7__ {scalar_t__ d3ddevice; scalar_t__ d3dcontext; } ;
struct TYPE_10__ {void* d3ddec; TYPE_2__ hw; TYPE_1__ d3d_dev; } ;
typedef  TYPE_4__ vlc_va_sys_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_QueryInterface (scalar_t__,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ID3D11DeviceContext_Release (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11Device_QueryInterface (scalar_t__,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ID3D11Device_Release (scalar_t__) ; 
 int /*<<< orphan*/  ID3D11VideoContext_Release (void*) ; 
 int /*<<< orphan*/  IID_ID3D11VideoContext ; 
 int /*<<< orphan*/  IID_ID3D11VideoDevice ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int D3dCreateDevice(vlc_va_t *va)
{
    vlc_va_sys_t *sys = va->sys;
    HRESULT hr;

    assert(sys->d3d_dev.d3ddevice && sys->d3d_dev.d3dcontext);
    void *d3dvidctx = NULL;
    hr = ID3D11DeviceContext_QueryInterface(sys->d3d_dev.d3dcontext, &IID_ID3D11VideoContext, &d3dvidctx);
    if (FAILED(hr)) {
       msg_Err(va, "Could not Query ID3D11VideoContext Interface. (hr=0x%lX)", hr);
       ID3D11DeviceContext_Release(sys->d3d_dev.d3dcontext);
       ID3D11Device_Release(sys->d3d_dev.d3ddevice);
       return VLC_EGENERIC;
    }
    sys->hw.video_context = d3dvidctx;

    void *d3dviddev = NULL;
    hr = ID3D11Device_QueryInterface(sys->d3d_dev.d3ddevice, &IID_ID3D11VideoDevice, &d3dviddev);
    if (FAILED(hr)) {
       msg_Err(va, "Could not Query ID3D11VideoDevice Interface. (hr=0x%lX)", hr);
       ID3D11DeviceContext_Release(sys->d3d_dev.d3dcontext);
       ID3D11Device_Release(sys->d3d_dev.d3ddevice);
       ID3D11VideoContext_Release(sys->hw.video_context);
       return VLC_EGENERIC;
    }
    sys->d3ddec = d3dviddev;

    return VLC_SUCCESS;
}