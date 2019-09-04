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
typedef  int WORD ;
typedef  int /*<<< orphan*/  VARIANTARG ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  EXCEPINFO ;
typedef  int /*<<< orphan*/  DISPPARAMS ;

/* Variables and functions */
 int DISPATCH_METHOD ; 
 int /*<<< orphan*/  DISP_E_EXCEPTION ; 
 int /*<<< orphan*/  DISP_E_MEMBERNOTFOUND ; 
 int /*<<< orphan*/  DispGetParam (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiInstallProductW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT_BSTR ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT InstallerImpl_InstallProduct(WORD wFlags,
                                            DISPPARAMS* pDispParams,
                                            VARIANT* pVarResult,
                                            EXCEPINFO* pExcepInfo,
                                            UINT* puArgErr)
{
    UINT ret;
    HRESULT hr;
    VARIANTARG varg0, varg1;

    if (!(wFlags & DISPATCH_METHOD))
        return DISP_E_MEMBERNOTFOUND;

    VariantInit(&varg0);
    hr = DispGetParam(pDispParams, 0, VT_BSTR, &varg0, puArgErr);
    if (FAILED(hr))
        return hr;

    VariantInit(&varg1);
    hr = DispGetParam(pDispParams, 1, VT_BSTR, &varg1, puArgErr);
    if (FAILED(hr))
        goto done;

    ret = MsiInstallProductW(V_BSTR(&varg0), V_BSTR(&varg1));
    if (ret != ERROR_SUCCESS)
    {
        hr = DISP_E_EXCEPTION;
        goto done;
    }

done:
    VariantClear(&varg0);
    VariantClear(&varg1);
    return hr;
}