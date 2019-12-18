#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  message; } ;
typedef  TYPE_1__ MSG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  void* HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_LOCAL_SERVER ; 
 int /*<<< orphan*/  CLSID_WineOOPTest ; 
 int /*<<< orphan*/  CloseHandle (void*) ; 
 int /*<<< orphan*/  CoRegisterClassObject (scalar_t__,...) ; 
 int /*<<< orphan*/  CoRevokeClassObject (scalar_t__) ; 
 void* CreateEventA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DispatchMessageA (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MsgWaitForMultipleObjects (int,void**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 scalar_t__ PeekMessageA (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QS_ALLINPUT ; 
 int /*<<< orphan*/  REGCLS_SINGLEUSE ; 
 int /*<<< orphan*/  SetEvent (void*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TestOOP_ClassFactory ; 
 int /*<<< orphan*/  TranslateMessage (TYPE_1__*) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 void* heventShutdown ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_ole_success (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (scalar_t__)) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_register_local_server(void)
{
    DWORD cookie;
    HRESULT hr;
    HANDLE ready_event;
    DWORD wait;
    HANDLE handles[2];

    heventShutdown = CreateEventA(NULL, TRUE, FALSE, NULL);
    ready_event = CreateEventA(NULL, FALSE, FALSE, "Wine COM Test Ready Event");
    handles[0] = CreateEventA(NULL, FALSE, FALSE, "Wine COM Test Quit Event");
    handles[1] = CreateEventA(NULL, FALSE, FALSE, "Wine COM Test Repeat Event");

again:
    hr = CoRegisterClassObject(&CLSID_WineOOPTest, (IUnknown *)&TestOOP_ClassFactory,
                               CLSCTX_LOCAL_SERVER, REGCLS_SINGLEUSE, &cookie);
    ok_ole_success(hr, CoRegisterClassObject);

    SetEvent(ready_event);

    do
    {
        wait = MsgWaitForMultipleObjects(2, handles, FALSE, 30000, QS_ALLINPUT);
        if (wait == WAIT_OBJECT_0+2)
        {
            MSG msg;

            if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
            {
                trace("Message 0x%x\n", msg.message);
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
        }
        else if (wait == WAIT_OBJECT_0+1)
        {
            hr = CoRevokeClassObject(cookie);
            ok_ole_success(hr, CoRevokeClassObject);
            goto again;
        }
    }
    while (wait == WAIT_OBJECT_0+2);

    ok( wait == WAIT_OBJECT_0, "quit event wait timed out\n" );
    hr = CoRevokeClassObject(cookie);
    ok_ole_success(hr, CoRevokeClassObject);
    CloseHandle(handles[0]);
    CloseHandle(handles[1]);
}