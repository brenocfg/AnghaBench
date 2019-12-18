#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vars ;
typedef  int /*<<< orphan*/  params ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int refCount; int /*<<< orphan*/ * pt; scalar_t__ ptCount; TYPE_1__ IConnectionPointContainer_iface; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int refCount; TYPE_2__ IDispatch_iface; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IConnectionPoint ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_3__ Disp ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DISPPARAMS ;
typedef  TYPE_4__ Contain ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IID_NULL ; 
 scalar_t__ IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VT_BSTR ; 
 int /*<<< orphan*/  VT_I4 ; 
 int /*<<< orphan*/  contain_vtbl ; 
 int /*<<< orphan*/  disp_vtbl ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pConnectToConnectionPoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ **) ; 
 scalar_t__ pIConnectionPoint_SimpleInvoke (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ pSHPackDispParams (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_IConnectionPoint(void)
{
    HRESULT rc;
    ULONG ref;
    IConnectionPoint *point;
    Contain *container;
    Disp *dispatch;
    DWORD cookie = 0xffffffff;
    DISPPARAMS params;
    VARIANT vars[10];

    container = HeapAlloc(GetProcessHeap(),0,sizeof(Contain));
    container->IConnectionPointContainer_iface.lpVtbl = &contain_vtbl;
    container->refCount = 1;
    container->ptCount = 0;
    container->pt = NULL;

    dispatch = HeapAlloc(GetProcessHeap(),0,sizeof(Disp));
    dispatch->IDispatch_iface.lpVtbl = &disp_vtbl;
    dispatch->refCount = 1;

    rc = pConnectToConnectionPoint((IUnknown*)dispatch, &IID_NULL, TRUE, (IUnknown*)container, &cookie, &point);
    ok(rc == S_OK, "pConnectToConnectionPoint failed with %x\n",rc);
    ok(point != NULL, "returned ConnectionPoint is NULL\n");
    ok(cookie != 0xffffffff, "invalid cookie returned\n");

    rc = pIConnectionPoint_SimpleInvoke(point,0xa0,NULL);
    ok(rc == S_OK, "pConnectToConnectionPoint failed with %x\n",rc);

    memset(&params, 0xc0, sizeof(params));
    memset(vars, 0xc0, sizeof(vars));
    rc = pSHPackDispParams(&params, vars, 2, VT_I4, 0xdeadbeef, VT_BSTR, 0xdeadcafe);
    ok(rc == S_OK, "SHPackDispParams failed: %08x\n", rc);

    rc = pIConnectionPoint_SimpleInvoke(point,0xa1,&params);
    ok(rc == S_OK, "pConnectToConnectionPoint failed with %x\n",rc);

    rc = pConnectToConnectionPoint(NULL, &IID_NULL, FALSE, (IUnknown*)container, &cookie, NULL);
    ok(rc == S_OK, "pConnectToConnectionPoint failed with %x\n",rc);

/* MSDN says this should be required but it crashs on XP
    IUnknown_Release(point);
*/
    ref = IUnknown_Release((IUnknown*)container);
    ok(ref == 0, "leftover IConnectionPointContainer reference %i\n",ref);
    ref = IUnknown_Release((IUnknown*)dispatch);
    ok(ref == 0, "leftover IDispatch reference %i\n",ref);
}