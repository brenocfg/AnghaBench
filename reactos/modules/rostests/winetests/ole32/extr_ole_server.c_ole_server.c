#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  IClassFactory_iface; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_SERVER ; 
 int /*<<< orphan*/  CLSID_WineTestObject ; 
 int /*<<< orphan*/  COINIT_MULTITHREADED ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CoInitializeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ CoRegisterClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoRevokeClassObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  EVENT_MODIFY_STATE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentProcessId () ; 
 int GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ OpenEventA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  REGCLS_MULTIPLEUSE ; 
 int /*<<< orphan*/  SYNCHRONIZE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SetEvent (scalar_t__) ; 
 int /*<<< orphan*/  WaitForSingleObject (scalar_t__,int /*<<< orphan*/ ) ; 
 int class_ref ; 
 TYPE_1__ factory ; 
 int obj_ref ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int server_locks ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void ole_server(void)
{
    HRESULT hr;
    DWORD key;

    trace("server: starting %u\n", GetCurrentProcessId());

    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (hr == S_OK)
    {
        trace("server: registering class object\n");
        hr = CoRegisterClassObject(&CLSID_WineTestObject, (IUnknown *)&factory.IClassFactory_iface,
                                   CLSCTX_SERVER, REGCLS_MULTIPLEUSE, &key);
        if (hr == S_OK)
        {
            HANDLE done_event, init_done_event;

            done_event = OpenEventA(SYNCHRONIZE, FALSE, "ole_server_done_event");
            ok(done_event != 0, "server: OpenEvent error %d\n", GetLastError());
            init_done_event = OpenEventA(EVENT_MODIFY_STATE, FALSE, "ole_server_init_done_event");
            ok(init_done_event != 0, "server: OpenEvent error %d\n", GetLastError());

            SetEvent(init_done_event);

            trace("server: waiting for requests\n");
            WaitForSingleObject(done_event, INFINITE);

            /* 1 remainining class ref is supposed to be cleared by CoRevokeClassObject */
            ok(class_ref == 1, "expected 1 class refs, got %d\n", class_ref);
            ok(!obj_ref, "expected 0 object refs, got %d\n", obj_ref);
            ok(!server_locks, "expected 0 server locks, got %d\n", server_locks);

            CloseHandle(done_event);
            CloseHandle(init_done_event);
            if (0)
            {
                /* calling CoRevokeClassObject terminates process under Win7 */
                trace("call CoRevokeClassObject\n");
                CoRevokeClassObject(key);
                trace("ret CoRevokeClassObject\n");
            }
        }
        trace("server: call CoUninitialize\n");
        CoUninitialize();
        trace("server: ret CoUninitialize\n");
    }

    trace("server: exiting %u\n", GetCurrentProcessId());
}