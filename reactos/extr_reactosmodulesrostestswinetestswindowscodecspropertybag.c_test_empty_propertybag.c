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
typedef  int /*<<< orphan*/  IWICComponentFactory ;
typedef  int /*<<< orphan*/  IPropertyBag2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_WICImagingFactory ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IID_IWICComponentFactory ; 
 int /*<<< orphan*/  IPropertyBag2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWICComponentFactory_CreateEncoderPropertyBag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWICComponentFactory_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_propertybag_countproperties (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_propertybag_getpropertyinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_empty_propertybag(void)
{
    HRESULT hr;
    IWICComponentFactory *factory;
    IPropertyBag2 *property;

    hr = CoCreateInstance(&CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IWICComponentFactory, (void**)&factory);
    ok(hr == S_OK, "CoCreateInstance failed, hr=%x\n", hr);

    hr = IWICComponentFactory_CreateEncoderPropertyBag(factory, NULL, 0, &property);

    ok(hr == S_OK, "Creating EncoderPropertyBag failed, hr=%x\n", hr);
    if (FAILED(hr)) return;

    test_propertybag_countproperties(property, 0);

    test_propertybag_getpropertyinfo(property, 0);

    IPropertyBag2_Release(property);

    IWICComponentFactory_Release(factory);
}