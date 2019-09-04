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
typedef  int /*<<< orphan*/  REFCLSID ;
typedef  int /*<<< orphan*/  IWICComponentInfo ;
typedef  int /*<<< orphan*/  IWICBitmapDecoderInfo ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CreateComponentInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IWICBitmapDecoderInfo ; 
 int /*<<< orphan*/  IWICComponentInfo_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IWICComponentInfo_Release (int /*<<< orphan*/ *) ; 

HRESULT get_decoder_info(REFCLSID clsid, IWICBitmapDecoderInfo **info)
{
    IWICComponentInfo *compinfo;
    HRESULT hr;

    hr = CreateComponentInfo(clsid, &compinfo);
    if (FAILED(hr)) return hr;

    hr = IWICComponentInfo_QueryInterface(compinfo, &IID_IWICBitmapDecoderInfo,
        (void **)info);

    IWICComponentInfo_Release(compinfo);

    return hr;
}