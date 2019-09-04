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
typedef  int /*<<< orphan*/  VARTYPE ;
typedef  int /*<<< orphan*/  VARIANTARG ;
struct TYPE_3__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ DISPPARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_PROPERTYGET ; 
 int /*<<< orphan*/  DISPID_VALUE ; 
 int /*<<< orphan*/  DISP_E_BADVARTYPE ; 
 int /*<<< orphan*/  DISP_E_TYPEMISMATCH ; 
 int /*<<< orphan*/  IDispatch_Invoke (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_NULL ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARIANT_CopyData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  VariantChangeTypeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT VARIANT_FromDisp(IDispatch* pdispIn, LCID lcid, void* pOut,
                                VARTYPE vt, DWORD dwFlags)
{
  static DISPPARAMS emptyParams = { NULL, NULL, 0, 0 };
  VARIANTARG srcVar, dstVar;
  HRESULT hRet;

  if (!pdispIn)
    return DISP_E_BADVARTYPE;

  /* Get the default 'value' property from the IDispatch */
  VariantInit(&srcVar);
  hRet = IDispatch_Invoke(pdispIn, DISPID_VALUE, &IID_NULL, lcid, DISPATCH_PROPERTYGET,
                          &emptyParams, &srcVar, NULL, NULL);

  if (SUCCEEDED(hRet))
  {
    /* Convert the property to the requested type */
    VariantInit(&dstVar);
    hRet = VariantChangeTypeEx(&dstVar, &srcVar, lcid, dwFlags, vt);
    VariantClear(&srcVar);

    if (SUCCEEDED(hRet))
      VARIANT_CopyData(&dstVar, vt, pOut);
  }
  else
    hRet = DISP_E_TYPEMISMATCH;
  return hRet;
}