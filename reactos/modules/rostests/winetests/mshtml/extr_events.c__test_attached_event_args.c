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
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_3__ {int cArgs; int /*<<< orphan*/ * rgvarg; int /*<<< orphan*/  rgdispidNamedArgs; int /*<<< orphan*/  cNamedArgs; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLEventObj ;
typedef  int /*<<< orphan*/  EXCEPINFO ;
typedef  TYPE_1__ DISPPARAMS ;
typedef  scalar_t__ DISPID ;

/* Variables and functions */
 scalar_t__ DISPATCH_METHOD ; 
 scalar_t__ DISPID_VALUE ; 
 int /*<<< orphan*/  IHTMLEventObj_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VT_DISPATCH ; 
 int /*<<< orphan*/  VT_EMPTY ; 
 int /*<<< orphan*/ * V_DISPATCH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _get_event_obj (unsigned int) ; 
 int /*<<< orphan*/  iface_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void _test_attached_event_args(unsigned line, DISPID id, WORD wFlags, DISPPARAMS *pdp,
        VARIANT *pvarRes, EXCEPINFO *pei)
{
    IHTMLEventObj *event;

    ok(id == DISPID_VALUE, "id = %d\n", id);
    ok(wFlags == DISPATCH_METHOD, "wFlags = %x\n", wFlags);
    ok(pdp != NULL, "pDispParams == NULL\n");
    ok(pdp->cArgs == 1, "pdp->cArgs = %d\n", pdp->cArgs);
    ok(!pdp->cNamedArgs, "pdp->cNamedArgs = %d\n", pdp->cNamedArgs);
    ok(!pdp->rgdispidNamedArgs, "pdp->rgdispidNamedArgs = %p\n", pdp->rgdispidNamedArgs);
    ok(pdp->rgvarg != NULL, "rgvarg = NULL\n");
    ok(pvarRes != NULL, "pvarRes = NULL\n");
    ok(pei != NULL, "pei = NULL\n");
    ok(V_VT(pvarRes) == VT_EMPTY, "V_VT(pVarRes) = %d\n", V_VT(pvarRes));
    ok(V_VT(pdp->rgvarg) == VT_DISPATCH, "V_VT(pdp->rgvarg) = %d\n", V_VT(pdp->rgvarg));
    ok(V_DISPATCH(pdp->rgvarg) != NULL, "V_DISPATCH(pdp->rgvarg) = %p\n", V_DISPATCH(pdp->rgvarg));

    event = _get_event_obj(line);
    ok(iface_cmp((IUnknown*)event, (IUnknown*)V_DISPATCH(pdp->rgvarg)), "event != arg0\n");
    IHTMLEventObj_Release(event);
}