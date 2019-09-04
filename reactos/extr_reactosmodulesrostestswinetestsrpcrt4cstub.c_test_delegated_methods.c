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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITest1 ;
typedef  int /*<<< orphan*/  IPSFactoryBuffer ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSCTX_LOCAL_SERVER ; 
 int /*<<< orphan*/  CLSID_test1 ; 
 int /*<<< orphan*/  CLSID_test_ps ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int CoRegisterClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CoRegisterPSClsid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int CoRevokeClassObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateEventA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_IPSFactoryBuffer ; 
 int /*<<< orphan*/  IID_ITest1 ; 
 int ITest1_GetClassID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITest1_Release (int /*<<< orphan*/ *) ; 
 int ITest1_square (int /*<<< orphan*/ *,int) ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int NdrDllGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REGCLS_MULTIPLEUSE ; 
 int S_OK ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aProxyFileList ; 
 int /*<<< orphan*/  create_process (char*) ; 
 int /*<<< orphan*/  gPFactory ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_delegated_methods(void)
{
    HANDLE process, stop_event, ready_event;
    IPSFactoryBuffer *ps;
    ITest1 *test_obj;
    DWORD ps_cookie;
    CLSID clsid;
    HRESULT hr;
    int ret;

    stop_event = CreateEventA(NULL, TRUE, FALSE, "wine_cstub_test_server_stop");
    ready_event = CreateEventA(NULL, TRUE, FALSE, "wine_cstub_test_server_ready");

    process = create_process("server");
    ok(!WaitForSingleObject(ready_event, 1000), "wait failed\n");

    hr = NdrDllGetClassObject(&CLSID_test_ps, &IID_IPSFactoryBuffer, (void **)&ps,
        &aProxyFileList, &CLSID_test_ps, &gPFactory);
    ok(hr == S_OK, "got %#x\n", hr);

    hr = CoRegisterClassObject(&CLSID_test_ps, (IUnknown *)ps,
        CLSCTX_INPROC_SERVER, REGCLS_MULTIPLEUSE, &ps_cookie);
    ok(hr == S_OK, "got %#x\n", hr);

    hr = CoRegisterPSClsid(&IID_ITest1, &CLSID_test_ps);
    ok(hr == S_OK, "got %#x\n", hr);

    hr = CoCreateInstance(&CLSID_test1, NULL, CLSCTX_LOCAL_SERVER, &IID_ITest1, (void **)&test_obj);
    ok(hr == S_OK, "got %#x\n", hr);

    ret = ITest1_square(test_obj, 3);
    ok(ret == 9, "got %d\n", ret);

    hr = ITest1_GetClassID(test_obj, &clsid);
    ok(hr == S_OK, "got %#x\n", hr);
    ok(IsEqualGUID(&clsid, &CLSID_test1), "got %s\n", wine_dbgstr_guid(&clsid));

    ITest1_Release(test_obj);

    SetEvent(stop_event);
    ok(!WaitForSingleObject(process, 1000), "wait failed\n");

    hr = CoRevokeClassObject(ps_cookie);
    ok(hr == S_OK, "got %#x\n", hr);
}