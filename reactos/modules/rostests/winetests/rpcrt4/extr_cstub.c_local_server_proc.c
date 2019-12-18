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
typedef  int /*<<< orphan*/  IPSFactoryBuffer ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSCTX_LOCAL_SERVER ; 
 int /*<<< orphan*/  CLSID_test1 ; 
 int /*<<< orphan*/  CLSID_test_ps ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 scalar_t__ CoRegisterClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ CoRegisterPSClsid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CoRevokeClassObject (scalar_t__) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 scalar_t__ CoWaitForMultipleHandles (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  EVENT_ALL_ACCESS ; 
 int /*<<< orphan*/  ExitProcess (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_IPSFactoryBuffer ; 
 int /*<<< orphan*/  IID_ITest1 ; 
 scalar_t__ NdrDllGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenEventA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  REGCLS_MULTIPLEUSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aProxyFileList ; 
 int /*<<< orphan*/  gPFactory ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_cf ; 

__attribute__((used)) static void local_server_proc(void)
{
    DWORD obj_cookie, ps_cookie, index;
    HANDLE stop_event, ready_event;
    IPSFactoryBuffer *ps;
    HRESULT hr;

    stop_event = OpenEventA(EVENT_ALL_ACCESS, FALSE, "wine_cstub_test_server_stop");
    ready_event = OpenEventA(EVENT_ALL_ACCESS, FALSE, "wine_cstub_test_server_ready");

    CoInitialize(NULL);

    hr = CoRegisterClassObject(&CLSID_test1, (IUnknown *)&test_cf,
        CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &obj_cookie);
    ok(hr == S_OK, "got %#x\n", hr);

    hr = NdrDllGetClassObject(&CLSID_test_ps, &IID_IPSFactoryBuffer, (void **)&ps,
        &aProxyFileList, &CLSID_test_ps, &gPFactory);
    ok(hr == S_OK, "got %#x\n", hr);

    hr = CoRegisterClassObject(&CLSID_test_ps, (IUnknown *)ps,
        CLSCTX_INPROC_SERVER, REGCLS_MULTIPLEUSE, &ps_cookie);
    ok(hr == S_OK, "got %#x\n", hr);

    hr = CoRegisterPSClsid(&IID_ITest1, &CLSID_test_ps);
    ok(hr == S_OK, "got %#x\n", hr);

    SetEvent(ready_event);

    hr = CoWaitForMultipleHandles(0, 1000, 1, &stop_event, &index);
    ok(hr == S_OK, "got %#x\n", hr);
    ok(!index, "got %u\n", index);

    hr = CoRevokeClassObject(ps_cookie);
    ok(hr == S_OK, "got %#x\n", hr);

    hr = CoRevokeClassObject(obj_cookie);
    ok(hr == S_OK, "got %#x\n", hr);

    CoUninitialize();
    ExitProcess(0);
}