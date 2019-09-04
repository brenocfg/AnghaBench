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
typedef  int /*<<< orphan*/  MSG ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_CACHE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClipTestProc ; 
 int /*<<< orphan*/  ClipThread ; 
 int /*<<< orphan*/  CloseClipboard () ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateWindowW (char*,char*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CritSect ; 
 int /*<<< orphan*/  EMPTY_CACHE () ; 
 int /*<<< orphan*/  EmptyClipboard () ; 
 int /*<<< orphan*/  EmptyClipboard_chain ; 
 int /*<<< orphan*/  FlushMessages () ; 
 scalar_t__ GetMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OpenClipboard (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RecordAndDispatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegisterSimpleClass (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WS_OVERLAPPEDWINDOW ; 
 int /*<<< orphan*/  empty_chain ; 
 int /*<<< orphan*/ * hWnd1 ; 
 int /*<<< orphan*/ * hWnd2 ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

void TestMessages()
{
    HANDLE hThread;
    DWORD dwThread;
    BOOL ret;
    MSG msg;

    /* Initialize the test */
    InitializeCriticalSection(&CritSect);

    RegisterSimpleClass(ClipTestProc, L"clipstest");

    hWnd2 = NULL;
    hWnd1 = CreateWindowW(L"clipstest", L"clipstest", WS_OVERLAPPEDWINDOW,
                        20, 20, 300, 300, NULL, NULL, 0, NULL);
    ok (hWnd1 != NULL, "CreateWindowW failed\n");

    EMPTY_CACHE();

    /* Get ownership of the clipboard and record the messages we get */
    ret = OpenClipboard(hWnd1);
    ok (ret, "OpenClipboard failed\n");

    ret = EmptyClipboard();
    ok (ret, "EmptyClipboard failed\n");

    ret = CloseClipboard();
    ok (ret, "CloseClipboard failed\n");

    /* Record posted messages */
    FlushMessages();
    COMPARE_CACHE(empty_chain);

    /* Create the child thread and record messages till we get the WM_QUIT */
    hThread = CreateThread(NULL, 0, ClipThread, NULL, 0, &dwThread);

    while (GetMessage(&msg, 0, 0 ,0))
        RecordAndDispatch(&msg);

    COMPARE_CACHE(EmptyClipboard_chain);

    CloseHandle(hThread);
}