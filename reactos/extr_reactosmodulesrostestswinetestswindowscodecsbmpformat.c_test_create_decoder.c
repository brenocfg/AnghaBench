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
typedef  int /*<<< orphan*/  IWICImagingFactory ;
typedef  int /*<<< orphan*/  IWICBitmapDecoder ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_WICImagingFactory ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  GUID_ContainerFormatBmp ; 
 int /*<<< orphan*/  GUID_VendorMicrosoft ; 
 int /*<<< orphan*/  IID_IWICImagingFactory ; 
 int /*<<< orphan*/  IWICBitmapDecoder_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWICImagingFactory_CreateDecoder (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWICImagingFactory_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_create_decoder(void)
{
    IWICBitmapDecoder *decoder;
    IWICImagingFactory *factory;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
        &IID_IWICImagingFactory, (void **)&factory);
    ok(hr == S_OK, "CoCreateInstance error %#x\n", hr);

    hr = IWICImagingFactory_CreateDecoder(factory, NULL, NULL, NULL);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %#x\n", hr);

    hr = IWICImagingFactory_CreateDecoder(factory, NULL, NULL, &decoder);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %#x\n", hr);

    hr = IWICImagingFactory_CreateDecoder(factory, &GUID_ContainerFormatBmp, NULL, &decoder);
    ok(hr == S_OK, "CreateDecoder error %#x\n", hr);
    IWICBitmapDecoder_Release(decoder);

    hr = IWICImagingFactory_CreateDecoder(factory, &GUID_ContainerFormatBmp, &GUID_VendorMicrosoft, &decoder);
    ok(hr == S_OK, "CreateDecoder error %#x\n", hr);
    IWICBitmapDecoder_Release(decoder);

    IWICImagingFactory_Release(factory);
}