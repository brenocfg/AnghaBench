#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  d3ddevice; } ;
struct TYPE_7__ {TYPE_1__ d3d_dev; } ;
typedef  TYPE_2__ vlc_va_sys_t ;
struct TYPE_8__ {scalar_t__ VendorId; } ;
typedef  int /*<<< orphan*/  IDXGIAdapter ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ DXGI_ADAPTER_DESC ;

/* Variables and functions */
 int /*<<< orphan*/ * D3D11DeviceAdapter (int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ GPU_MANUFACTURER_QUALCOMM ; 
 int /*<<< orphan*/  IDXGIAdapter_GetDesc (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  IDXGIAdapter_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool CanUseDecoderPadding(vlc_va_sys_t *sys)
{
    IDXGIAdapter *pAdapter = D3D11DeviceAdapter(sys->d3d_dev.d3ddevice);
    if (!pAdapter)
        return false;

    DXGI_ADAPTER_DESC adapterDesc;
    HRESULT hr = IDXGIAdapter_GetDesc(pAdapter, &adapterDesc);
    IDXGIAdapter_Release(pAdapter);
    if (FAILED(hr))
        return false;

    /* Qualcomm hardware has issues with textures and pixels that should not be
    * part of the decoded area */
    return adapterDesc.VendorId != GPU_MANUFACTURER_QUALCOMM;
}