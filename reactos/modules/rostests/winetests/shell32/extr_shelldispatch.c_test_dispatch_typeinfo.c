#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/  guid; } ;
typedef  TYPE_1__ TYPEATTR ;
typedef  int /*<<< orphan*/ * REFIID ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int HRESULT ;

/* Variables and functions */
 int IDispatch_GetTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int IDispatch_GetTypeInfoCount (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IID_NULL ; 
 int ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_dispatch_typeinfo(IDispatch *disp, REFIID *riid)
{
    ITypeInfo *typeinfo;
    TYPEATTR *typeattr;
    UINT count;
    HRESULT hr;

    count = 10;
    hr = IDispatch_GetTypeInfoCount(disp, &count);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(count == 1, "got %u\n", count);

    hr = IDispatch_GetTypeInfo(disp, 0, LOCALE_SYSTEM_DEFAULT, &typeinfo);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = ITypeInfo_GetTypeAttr(typeinfo, &typeattr);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    while (!IsEqualGUID(*riid, &IID_NULL)) {
        if (IsEqualGUID(&typeattr->guid, *riid))
            break;
        riid++;
    }
    ok(IsEqualGUID(&typeattr->guid, *riid), "unexpected type guid %s\n", wine_dbgstr_guid(&typeattr->guid));

    ITypeInfo_ReleaseTypeAttr(typeinfo, typeattr);
    ITypeInfo_Release(typeinfo);
}