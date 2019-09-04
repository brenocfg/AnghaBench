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
struct TYPE_3__ {int /*<<< orphan*/  pIID; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ MULTI_QI ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_WineOOPTest ; 
 scalar_t__ CoCreateInstanceEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 scalar_t__ CoRegisterClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CoRevokeClassObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_IMoniker ; 
 int /*<<< orphan*/  IID_NULL ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGCLS_MULTIPLEUSE ; 
 int /*<<< orphan*/  Test_ClassFactory ; 
 int /*<<< orphan*/  create_instance_iid ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ok_ole_success (scalar_t__,char*) ; 
 scalar_t__ wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_CoCreateInstanceEx(void)
{
    MULTI_QI qi_res = { &IID_IMoniker };
    DWORD cookie;
    HRESULT hr;

    CoInitialize(NULL);

    hr = CoRegisterClassObject(&CLSID_WineOOPTest, (IUnknown *)&Test_ClassFactory,
                               CLSCTX_INPROC_SERVER, REGCLS_MULTIPLEUSE, &cookie);
    ok_ole_success(hr, "CoRegisterClassObject");

    create_instance_iid = IID_NULL;
    hr = CoCreateInstanceEx(&CLSID_WineOOPTest, NULL, CLSCTX_INPROC_SERVER, NULL, 1, &qi_res);
    ok(hr == E_NOINTERFACE, "CoCreateInstanceEx failed: %08x\n", hr);
    ok(IsEqualGUID(&create_instance_iid, qi_res.pIID), "Unexpected CreateInstance iid %s\n",
       wine_dbgstr_guid(&create_instance_iid));

    hr = CoRevokeClassObject(cookie);
    ok_ole_success(hr, "CoRevokeClassObject");

    CoUninitialize();
}