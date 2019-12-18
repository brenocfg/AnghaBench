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
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DISPPARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_PROPERTYGET ; 
 int /*<<< orphan*/  VT_DISPATCH ; 
 int /*<<< orphan*/ * V_DISPATCH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  invoke (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT Session_Database(IDispatch *pSession, IDispatch **pDatabase)
{
    VARIANT varresult;
    DISPPARAMS dispparams = {NULL, NULL, 0, 0};
    HRESULT hr;

    hr = invoke(pSession, "Database", DISPATCH_PROPERTYGET, &dispparams, &varresult, VT_DISPATCH);
    *pDatabase = V_DISPATCH(&varresult);
    return hr;
}