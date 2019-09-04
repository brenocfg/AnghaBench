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
struct TYPE_3__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  LPVARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DISPPARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_PROPERTYGET ; 
 int /*<<< orphan*/  DISPID_VALUE ; 
 int /*<<< orphan*/  DISP_E_TYPEMISMATCH ; 
 int /*<<< orphan*/  IDispatch_Invoke (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_NULL ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int VT_DISPATCH ; 
 int VT_TYPEMASK ; 
 int /*<<< orphan*/ * V_DISPATCH (int /*<<< orphan*/ ) ; 
 int V_VT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT VARIANT_FetchDispatchValue(LPVARIANT pvDispatch, LPVARIANT pValue)
{
    HRESULT hres;
    static DISPPARAMS emptyParams = { NULL, NULL, 0, 0 };

    if ((V_VT(pvDispatch) & VT_TYPEMASK) == VT_DISPATCH) {
        if (NULL == V_DISPATCH(pvDispatch)) return DISP_E_TYPEMISMATCH;
        hres = IDispatch_Invoke(V_DISPATCH(pvDispatch), DISPID_VALUE, &IID_NULL,
            LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &emptyParams, pValue,
            NULL, NULL);
    } else {
        hres = DISP_E_TYPEMISMATCH;
    }
    return hres;
}