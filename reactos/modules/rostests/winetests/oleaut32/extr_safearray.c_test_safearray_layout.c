#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ref; int /*<<< orphan*/  IRecordInfo_iface; } ;
struct TYPE_6__ {int cElements; scalar_t__ lLbound; } ;
typedef  TYPE_1__ SAFEARRAYBOUND ;
typedef  int /*<<< orphan*/  SAFEARRAY ;
typedef  TYPE_2__ IRecordInfoImpl ;
typedef  int /*<<< orphan*/  IRecordInfo ;
typedef  int /*<<< orphan*/ * HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/ * DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 TYPE_2__* IRecordInfoImpl_Construct () ; 
 int /*<<< orphan*/  IRecordInfo_Release (int /*<<< orphan*/ *) ; 
 int IsEqualIID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/ * SafeArrayCreate (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/ * SafeArrayDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SafeArrayGetIID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SafeArraySetIID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VT_RECORD ; 
 int /*<<< orphan*/ * VT_UI1 ; 
 int /*<<< orphan*/ * VT_UNKNOWN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * pSafeArrayCreateEx (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_safearray_layout(void)
{
    IRecordInfoImpl *irec;
    IRecordInfo *record;
    GUID guid, *guidptr;
    SAFEARRAYBOUND sab;
    SAFEARRAY *sa;
    DWORD *dwptr;
    HRESULT hr;

    sab.lLbound = 0;
    sab.cElements = 10;

    /* GUID field */
    sa = SafeArrayCreate(VT_UNKNOWN, 1, &sab);
    ok(sa != NULL, "got %p\n", sa);

    guidptr = (GUID*)sa - 1;
    ok(IsEqualIID(guidptr, &IID_IUnknown), "got %s\n", wine_dbgstr_guid(guidptr));

    hr = SafeArraySetIID(sa, &IID_IDispatch);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(IsEqualIID(guidptr, &IID_IDispatch), "got %s\n", wine_dbgstr_guid(guidptr));

    memcpy(guidptr, &IID_IUnknown, sizeof(GUID));
    hr = SafeArrayGetIID(sa, &guid);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(IsEqualIID(&guid, &IID_IUnknown), "got %s\n", wine_dbgstr_guid(&guid));

    hr = SafeArrayDestroy(sa);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    /* VARTYPE field */
    sa = SafeArrayCreate(VT_UI1, 1, &sab);
    ok(sa != NULL, "got %p\n", sa);

    dwptr = (DWORD*)sa - 1;
    ok(*dwptr == VT_UI1, "got %d\n", *dwptr);

    hr = SafeArrayDestroy(sa);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    /* IRecordInfo pointer */
    irec = IRecordInfoImpl_Construct();
    irec->ref = 1;

    sa = pSafeArrayCreateEx(VT_RECORD, 1, &sab, &irec->IRecordInfo_iface);
    ok(sa != NULL, "failed to create array\n");

    record = *((IRecordInfo**)sa - 1);
    ok(record == &irec->IRecordInfo_iface, "got %p\n", record);

    hr = SafeArrayDestroy(sa);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    IRecordInfo_Release(&irec->IRecordInfo_iface);
}