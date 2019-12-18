#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_3__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DISPPARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_PROPERTYGET ; 
 int /*<<< orphan*/  VT_BSTR ; 
 scalar_t__ V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  invoke (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pInstaller ; 

__attribute__((used)) static HRESULT Installer_VersionGet(LPWSTR szVersion)
{
    VARIANT varresult;
    DISPPARAMS dispparams = {NULL, NULL, 0, 0};
    HRESULT hr;

    hr = invoke(pInstaller, "Version", DISPATCH_PROPERTYGET, &dispparams, &varresult, VT_BSTR);
    if (V_BSTR(&varresult)) lstrcpyW(szVersion, V_BSTR(&varresult));
    VariantClear(&varresult);
    return hr;
}