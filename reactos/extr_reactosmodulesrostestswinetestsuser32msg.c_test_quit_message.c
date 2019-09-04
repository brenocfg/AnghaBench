#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct recvd_message {int hwnd; int message; int flags; int wParam; int lParam; char* descr; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_6__ {int message; int wParam; int lParam; int hwnd; } ;
typedef  TYPE_1__ MSG ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowExA (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DialogBoxParamA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DispatchMessageA (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 int GetLastError () ; 
 int GetMessageA (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PM_NOREMOVE ; 
 int /*<<< orphan*/  PM_QS_SENDMESSAGE ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 int PeekMessageA (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostQuitMessage (int) ; 
 int PostThreadMessageA (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int WM_QUIT ; 
 int WM_USER ; 
 int /*<<< orphan*/  WS_OVERLAPPEDWINDOW ; 
 int /*<<< orphan*/  WmQuitDialogSeq ; 
 int /*<<< orphan*/  WmStopQuitSeq ; 
 int /*<<< orphan*/  add_message (struct recvd_message*) ; 
 int /*<<< orphan*/  flush_events () ; 
 int /*<<< orphan*/  flush_sequence () ; 
 int lparam ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_sequence (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int posted ; 
 int /*<<< orphan*/  wm_quit_dlg_proc ; 
 int wparam ; 

__attribute__((used)) static void test_quit_message(void)
{
    MSG msg;
    BOOL ret;

    /* test using PostQuitMessage */
    flush_events();
    PostQuitMessage(0xbeef);

    msg.message = 0;
    ret = PeekMessageA(&msg, 0, 0, 0, PM_QS_SENDMESSAGE);
    ok(!ret, "got %x message\n", msg.message);

    ret = PeekMessageA(&msg, NULL, 0, 0, PM_NOREMOVE);
    ok(ret, "PeekMessage failed with error %d\n", GetLastError());
    ok(msg.message == WM_QUIT, "Received message 0x%04x instead of WM_QUIT\n", msg.message);
    ok(msg.wParam == 0xbeef, "wParam was 0x%lx instead of 0xbeef\n", msg.wParam);

    ret = PostThreadMessageA(GetCurrentThreadId(), WM_USER, 0, 0);
    ok(ret, "PostMessage failed with error %d\n", GetLastError());

    ret = GetMessageA(&msg, NULL, 0, 0);
    ok(ret > 0, "GetMessage failed with error %d\n", GetLastError());
    ok(msg.message == WM_USER, "Received message 0x%04x instead of WM_USER\n", msg.message);

    /* note: WM_QUIT message received after WM_USER message */
    ret = GetMessageA(&msg, NULL, 0, 0);
    ok(!ret, "GetMessage return %d with error %d instead of FALSE\n", ret, GetLastError());
    ok(msg.message == WM_QUIT, "Received message 0x%04x instead of WM_QUIT\n", msg.message);
    ok(msg.wParam == 0xbeef, "wParam was 0x%lx instead of 0xbeef\n", msg.wParam);

    ret = PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE);
    ok( !ret || msg.message != WM_QUIT, "Received WM_QUIT again\n" );

    /* now test with PostThreadMessage - different behaviour! */
    PostThreadMessageA(GetCurrentThreadId(), WM_QUIT, 0xdead, 0);

    ret = PeekMessageA(&msg, NULL, 0, 0, PM_NOREMOVE);
    ok(ret, "PeekMessage failed with error %d\n", GetLastError());
    ok(msg.message == WM_QUIT, "Received message 0x%04x instead of WM_QUIT\n", msg.message);
    ok(msg.wParam == 0xdead, "wParam was 0x%lx instead of 0xdead\n", msg.wParam);

    ret = PostThreadMessageA(GetCurrentThreadId(), WM_USER, 0, 0);
    ok(ret, "PostMessage failed with error %d\n", GetLastError());

    /* note: we receive the WM_QUIT message first this time */
    ret = GetMessageA(&msg, NULL, 0, 0);
    ok(!ret, "GetMessage return %d with error %d instead of FALSE\n", ret, GetLastError());
    ok(msg.message == WM_QUIT, "Received message 0x%04x instead of WM_QUIT\n", msg.message);
    ok(msg.wParam == 0xdead, "wParam was 0x%lx instead of 0xdead\n", msg.wParam);

    ret = GetMessageA(&msg, NULL, 0, 0);
    ok(ret > 0, "GetMessage failed with error %d\n", GetLastError());
    ok(msg.message == WM_USER, "Received message 0x%04x instead of WM_USER\n", msg.message);

    flush_events();
    flush_sequence();
    ret = DialogBoxParamA(GetModuleHandleA(NULL), "TEST_EMPTY_DIALOG", 0, wm_quit_dlg_proc, 0);
    ok(ret == 1, "expected 1, got %d\n", ret);
    ok_sequence(WmQuitDialogSeq, "WmQuitDialogSeq", FALSE);
    memset(&msg, 0xab, sizeof(msg));
    ret = PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE);
    ok(ret, "PeekMessage failed\n");
    ok(msg.message == WM_QUIT, "Received message 0x%04x instead of WM_QUIT\n", msg.message);
    ok(msg.wParam == 0x1234, "wParam was 0x%lx instead of 0x1234\n", msg.wParam);
    ok(msg.lParam == 0, "lParam was 0x%lx instead of 0\n", msg.lParam);

    /* Check what happens to a WM_QUIT message posted to a window that gets
     * destroyed.
     */
    CreateWindowExA(0, "StopQuitClass", "Stop Quit Test", WS_OVERLAPPEDWINDOW,
                    0, 0, 100, 100, NULL, NULL, NULL, NULL);
    flush_sequence();
    while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
    {
        struct recvd_message rmsg;
        rmsg.hwnd = msg.hwnd;
        rmsg.message = msg.message;
        rmsg.flags = posted|wparam|lparam;
        rmsg.wParam = msg.wParam;
        rmsg.lParam = msg.lParam;
        rmsg.descr = "stop/quit";
        if (msg.message == WM_QUIT)
            /* The hwnd can only be checked here */
            ok(!msg.hwnd, "The WM_QUIT hwnd was %p instead of NULL\n", msg.hwnd);
        add_message(&rmsg);
        DispatchMessageA(&msg);
    }
    ok_sequence(WmStopQuitSeq, "WmStopQuitSeq", FALSE);
}