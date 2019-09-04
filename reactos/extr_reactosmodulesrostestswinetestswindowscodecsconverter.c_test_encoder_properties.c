#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_4__ {int /*<<< orphan*/ * pstrName; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ PROPBAG2 ;
typedef  int /*<<< orphan*/  IPropertyBag2 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_WICBmpEncoder ; 
 int /*<<< orphan*/  CLSID_WICJpegEncoder ; 
 int /*<<< orphan*/  CLSID_WICPngEncoder ; 
 int /*<<< orphan*/  CLSID_WICTiffEncoder ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IPropertyBag2_CountProperties (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ IPropertyBag2_GetPropertyInfo (int /*<<< orphan*/ *,int,int,TYPE_1__*,int*) ; 
 scalar_t__ IsEqualCLSID (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ WINCODEC_ERR_VALUEOUTOFRANGE ; 
 int min (int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_specific_encoder_properties (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  testdata_bmp_props ; 
 int /*<<< orphan*/  testdata_jpeg_props ; 
 int /*<<< orphan*/  testdata_png_props ; 
 int /*<<< orphan*/  testdata_tiff_props ; 

__attribute__((used)) static void test_encoder_properties(const CLSID* clsid_encoder, IPropertyBag2 *options)
{
    HRESULT hr;
    ULONG cProperties = 0;
    ULONG cProperties2 = 0;
    PROPBAG2 all_props[64] = {{0}}; /* Should be enough for every encoder out there */
    int i;

    /* CountProperties */
    {
        hr = IPropertyBag2_CountProperties(options, &cProperties);
        ok(SUCCEEDED(hr), "Reading property count, hr=%x\n", hr);
    }

    /* GetPropertyInfo */
    {
        hr = IPropertyBag2_GetPropertyInfo(options, cProperties, 1, all_props, &cProperties2);
        ok(hr == WINCODEC_ERR_VALUEOUTOFRANGE, "IPropertyBag2::GetPropertyInfo - iProperty out of bounce handled wrong, hr=%x\n", hr);

        hr = IPropertyBag2_GetPropertyInfo(options, 0, cProperties+1, all_props, &cProperties2);
        ok(hr == WINCODEC_ERR_VALUEOUTOFRANGE, "IPropertyBag2::GetPropertyInfo - cProperty out of bounce handled wrong, hr=%x\n", hr);

        if (cProperties == 0) /* GetPropertyInfo can be called for zero items on Windows 8 but not on Windows 7 (wine behaves like Win8) */
        {
            cProperties2 = cProperties;
            hr = S_OK;
        }
        else
        {
            hr = IPropertyBag2_GetPropertyInfo(options, 0, min(64, cProperties), all_props, &cProperties2);
            ok(SUCCEEDED(hr), "Reading infos from property bag failed, hr=%x\n", hr);
        }

        if (FAILED(hr))
            return;

        ok(cProperties == cProperties2, "Mismatch of property count (IPropertyBag2::CountProperties=%i, IPropertyBag2::GetPropertyInfo=%i)\n",
           (int)cProperties, (int)cProperties2);
    }

    if (IsEqualCLSID(clsid_encoder, &CLSID_WICTiffEncoder))
        test_specific_encoder_properties(options, testdata_tiff_props, all_props, cProperties2);
    else if (IsEqualCLSID(clsid_encoder, &CLSID_WICPngEncoder))
        test_specific_encoder_properties(options, testdata_png_props, all_props, cProperties2);
    else if (IsEqualCLSID(clsid_encoder, &CLSID_WICJpegEncoder))
        test_specific_encoder_properties(options, testdata_jpeg_props, all_props, cProperties2);
    else if (IsEqualCLSID(clsid_encoder, &CLSID_WICBmpEncoder))
        test_specific_encoder_properties(options, testdata_bmp_props, all_props, cProperties2);

    for (i=0; i < cProperties2; i++)
    {
        ok(all_props[i].pstrName != NULL, "Unset property name in output of IPropertyBag2::GetPropertyInfo\n");
        CoTaskMemFree(all_props[i].pstrName);
    }
}