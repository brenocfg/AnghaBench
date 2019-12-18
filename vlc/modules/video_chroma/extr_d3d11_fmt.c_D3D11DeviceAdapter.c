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
typedef  int /*<<< orphan*/  IDXGIDevice ;
typedef  int /*<<< orphan*/  IDXGIAdapter ;
typedef  int /*<<< orphan*/  ID3D11Device ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11Device_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDXGIDevice_GetAdapter (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDXGIDevice_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDXGIDevice ; 

IDXGIAdapter *D3D11DeviceAdapter(ID3D11Device *d3ddev)
{
    IDXGIDevice *pDXGIDevice = NULL;
    HRESULT hr = ID3D11Device_QueryInterface(d3ddev, &IID_IDXGIDevice, (void **)&pDXGIDevice);
    if (FAILED(hr)) {
        return NULL;
    }

    IDXGIAdapter *p_adapter;
    hr = IDXGIDevice_GetAdapter(pDXGIDevice, &p_adapter);
    IDXGIDevice_Release(pDXGIDevice);
    if (FAILED(hr)) {
        return NULL;
    }
    return p_adapter;
}