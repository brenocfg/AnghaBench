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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  IWICPixelFormatInfo2 ;
typedef  int /*<<< orphan*/  IWICComponentInfo ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IWICPixelFormatInfo ; 
 int /*<<< orphan*/  IID_IWICPixelFormatInfo2 ; 
 scalar_t__ IWICComponentInfo_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IWICComponentInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWICImagingFactory_CreateComponentInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 scalar_t__ IWICPixelFormatInfo2_GetBitsPerPixel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWICPixelFormatInfo2_GetChannelCount (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICPixelFormatInfo2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWICPixelFormatInfo2_SupportsTransparency (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  factory ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static HRESULT get_pixelformat_info(const GUID *format, UINT *bpp, UINT *channels, BOOL *trasparency)
{
    HRESULT hr;
    IWICComponentInfo *info;
    IWICPixelFormatInfo2 *formatinfo;

    hr = IWICImagingFactory_CreateComponentInfo(factory, format, &info);
    ok(hr == S_OK, "CreateComponentInfo(%s) error %#x\n", wine_dbgstr_guid(format), hr);
    if (hr == S_OK)
    {
        hr = IWICComponentInfo_QueryInterface(info, &IID_IWICPixelFormatInfo2, (void **)&formatinfo);
        if (hr == S_OK)
        {
            hr = IWICPixelFormatInfo2_SupportsTransparency(formatinfo, trasparency);
            ok(hr == S_OK, "SupportsTransparency error %#x\n", hr);
            IWICPixelFormatInfo2_Release(formatinfo);
        }
        hr = IWICComponentInfo_QueryInterface(info, &IID_IWICPixelFormatInfo, (void **)&formatinfo);
        if (hr == S_OK)
        {
            hr = IWICPixelFormatInfo2_GetBitsPerPixel(formatinfo, bpp);
            ok(hr == S_OK, "GetBitsPerPixel error %#x\n", hr);
            hr = IWICPixelFormatInfo2_GetChannelCount(formatinfo, channels);
            ok(hr == S_OK, "GetChannelCount error %#x\n", hr);
            IWICPixelFormatInfo2_Release(formatinfo);
        }
        IWICComponentInfo_Release(info);
    }
    return hr;
}