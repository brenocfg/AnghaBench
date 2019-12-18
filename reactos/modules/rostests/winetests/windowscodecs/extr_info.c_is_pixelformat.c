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
typedef  scalar_t__ WICComponentType ;
typedef  int /*<<< orphan*/  IWICComponentInfo ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  IWICComponentInfo_GetComponentType (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IWICComponentInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ WICPixelFormat ; 
 int /*<<< orphan*/  get_component_info (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static BOOL is_pixelformat(GUID *format)
{
    IWICComponentInfo *info;
    HRESULT hr;
    WICComponentType componenttype;

    hr = get_component_info(format, &info);
    if (FAILED(hr))
        return FALSE;

    hr = IWICComponentInfo_GetComponentType(info, &componenttype);

    IWICComponentInfo_Release(info);

    return SUCCEEDED(hr) && componenttype == WICPixelFormat;
}