#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wmCharSeq ;
struct message {int flags; size_t wParam; void* message; } ;
typedef  int /*<<< orphan*/  WNDPROC ;
typedef  size_t WCHAR ;
typedef  size_t UINT ;
struct TYPE_11__ {int MaxCharSize; size_t UnicodeDefaultChar; size_t* LeadByte; int /*<<< orphan*/  CodePageName; } ;
struct TYPE_9__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_10__ {void* message; size_t wParam; void* hwnd; int lParam; void* time; TYPE_1__ pt; } ;
typedef  TYPE_1__ POINT ;
typedef  TYPE_2__ MSG ;
typedef  void* HWND ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  void* DWORD ;
typedef  TYPE_3__ CPINFOEXA ;
typedef  size_t BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CallWindowProcA (int /*<<< orphan*/ ,void*,void*,size_t,int /*<<< orphan*/ ) ; 
 void* CreateWindowExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (void*) ; 
 int /*<<< orphan*/  DispatchMessageA (TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWLP_WNDPROC ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 int /*<<< orphan*/  GetMessageA (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetTickCount () ; 
 scalar_t__ GetWindowLongPtrA (void*,int /*<<< orphan*/ ) ; 
 int HIBYTE (size_t) ; 
 size_t MAX_LEADBYTES ; 
 int MultiByteToWideChar (void*,int /*<<< orphan*/ ,char*,int,size_t*,int) ; 
 int /*<<< orphan*/  PM_NOREMOVE ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 int /*<<< orphan*/  PeekMessageA (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PeekMessageW (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostMessageA (void*,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostMessageW (void*,void*,size_t,int) ; 
 int /*<<< orphan*/  PostThreadMessageA (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMTO_NORMAL ; 
 int /*<<< orphan*/  SendMessageA (void*,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageCallbackA (void*,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageTimeoutA (void*,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendNotifyMessageA (void*,void*,size_t,int /*<<< orphan*/ ) ; 
 void* WM_CHAR ; 
 void* WM_DEADCHAR ; 
 int /*<<< orphan*/  WM_MOUSEFIRST ; 
 int /*<<< orphan*/  WM_MOUSELAST ; 
 void* WM_SYSCHAR ; 
 int /*<<< orphan*/  WS_OVERLAPPEDWINDOW ; 
 int WideCharToMultiByte (void*,int /*<<< orphan*/ ,size_t*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct message* WmEmptySeq ; 
 int /*<<< orphan*/  flush_sequence () ; 
 void* get_input_codepage () ; 
 int /*<<< orphan*/  memset (struct message*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_sequence (struct message*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pGetCPInfoExA (void*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int sent ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 int /*<<< orphan*/  testWindowClassW ; 
 int /*<<< orphan*/  trace (char*,size_t,size_t,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int wparam ; 

__attribute__((used)) static void test_dbcs_wm_char(void)
{
    BYTE dbch[2];
    WCHAR wch, bad_wch;
    HWND hwnd, hwnd2;
    MSG msg;
    DWORD time;
    POINT pt;
    DWORD_PTR res;
    CPINFOEXA cpinfo;
    UINT i, j, k;
    struct message wmCharSeq[2];
    BOOL ret;
    DWORD cp = get_input_codepage();

    if (!pGetCPInfoExA)
    {
        win_skip("GetCPInfoExA is not available\n");
        return;
    }

    pGetCPInfoExA( cp, 0, &cpinfo );
    if (cpinfo.MaxCharSize != 2)
    {
        skip( "Skipping DBCS WM_CHAR test in SBCS codepage '%s'\n", cpinfo.CodePageName );
        return;
    }

    dbch[0] = dbch[1] = 0;
    wch = 0;
    bad_wch = cpinfo.UnicodeDefaultChar;
    for (i = 0; !wch && i < MAX_LEADBYTES && cpinfo.LeadByte[i]; i += 2)
        for (j = cpinfo.LeadByte[i]; !wch && j <= cpinfo.LeadByte[i+1]; j++)
            for (k = 128; k <= 255; k++)
            {
                char str[2];
                WCHAR wstr[2];
                str[0] = j;
                str[1] = k;
                if (MultiByteToWideChar( cp, 0, str, 2, wstr, 2 ) == 1 &&
                    WideCharToMultiByte( cp, 0, wstr, 1, str, 2, NULL, NULL ) == 2 &&
                    (BYTE)str[0] == j && (BYTE)str[1] == k &&
                    HIBYTE(wstr[0]) && HIBYTE(wstr[0]) != 0xff)
                {
                    dbch[0] = j;
                    dbch[1] = k;
                    wch = wstr[0];
                    break;
                }
            }

    if (!wch)
    {
        skip( "Skipping DBCS WM_CHAR test, no appropriate char found\n" );
        return;
    }
    trace( "using dbcs char %02x,%02x wchar %04x bad wchar %04x codepage '%s'\n",
           dbch[0], dbch[1], wch, bad_wch, cpinfo.CodePageName );

    hwnd = CreateWindowExW(0, testWindowClassW, NULL,
                           WS_OVERLAPPEDWINDOW, 100, 100, 200, 200, 0, 0, 0, NULL);
    hwnd2 = CreateWindowExW(0, testWindowClassW, NULL,
                           WS_OVERLAPPEDWINDOW, 100, 100, 200, 200, 0, 0, 0, NULL);
    ok (hwnd != 0, "Failed to create overlapped window\n");
    ok (hwnd2 != 0, "Failed to create overlapped window\n");
    flush_sequence();

    memset( wmCharSeq, 0, sizeof(wmCharSeq) );
    wmCharSeq[0].message = WM_CHAR;
    wmCharSeq[0].flags = sent|wparam;
    wmCharSeq[0].wParam = wch;

    /* posted message */
    PostMessageA( hwnd, WM_CHAR, dbch[0], 0 );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );
    PostMessageA( hwnd, WM_CHAR, dbch[1], 0 );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( ret, "no message\n" );
    ok( msg.message == WM_CHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == wch, "bad wparam %lx/%x\n", msg.wParam, wch );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );

    /* posted thread message */
    PostThreadMessageA( GetCurrentThreadId(), WM_CHAR, dbch[0], 0 );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );
    PostMessageA( hwnd, WM_CHAR, dbch[1], 0 );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( ret, "no message\n" );
    ok( msg.message == WM_CHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == wch, "bad wparam %lx/%x\n", msg.wParam, wch );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );

    /* sent message */
    flush_sequence();
    SendMessageA( hwnd, WM_CHAR, dbch[0], 0 );
    ok_sequence( WmEmptySeq, "no messages", FALSE );
    SendMessageA( hwnd, WM_CHAR, dbch[1], 0 );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );

    /* sent message with timeout */
    flush_sequence();
    SendMessageTimeoutA( hwnd, WM_CHAR, dbch[0], 0, SMTO_NORMAL, 0, &res );
    ok_sequence( WmEmptySeq, "no messages", FALSE );
    SendMessageTimeoutA( hwnd, WM_CHAR, dbch[1], 0, SMTO_NORMAL, 0, &res );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );

    /* sent message with timeout and callback */
    flush_sequence();
    SendMessageTimeoutA( hwnd, WM_CHAR, dbch[0], 0, SMTO_NORMAL, 0, &res );
    ok_sequence( WmEmptySeq, "no messages", FALSE );
    SendMessageCallbackA( hwnd, WM_CHAR, dbch[1], 0, NULL, 0 );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );

    /* sent message with callback */
    flush_sequence();
    SendNotifyMessageA( hwnd, WM_CHAR, dbch[0], 0 );
    ok_sequence( WmEmptySeq, "no messages", FALSE );
    SendMessageCallbackA( hwnd, WM_CHAR, dbch[1], 0, NULL, 0 );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );

    /* direct window proc call */
    flush_sequence();
    CallWindowProcA( (WNDPROC)GetWindowLongPtrA( hwnd, GWLP_WNDPROC ), hwnd, WM_CHAR, dbch[0], 0 );
    ok_sequence( WmEmptySeq, "no messages", FALSE );
    CallWindowProcA( (WNDPROC)GetWindowLongPtrA( hwnd, GWLP_WNDPROC ), hwnd, WM_CHAR, dbch[1], 0 );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );

    /* dispatch message */
    msg.hwnd = hwnd;
    msg.message = WM_CHAR;
    msg.wParam = dbch[0];
    msg.lParam = 0;
    DispatchMessageA( &msg );
    ok_sequence( WmEmptySeq, "no messages", FALSE );
    msg.wParam = dbch[1];
    DispatchMessageA( &msg );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );

    /* window handle is irrelevant */
    flush_sequence();
    SendMessageA( hwnd2, WM_CHAR, dbch[0], 0 );
    ok_sequence( WmEmptySeq, "no messages", FALSE );
    SendMessageA( hwnd, WM_CHAR, dbch[1], 0 );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );

    /* interleaved post and send */
    flush_sequence();
    PostMessageA( hwnd2, WM_CHAR, dbch[0], 0 );
    SendMessageA( hwnd2, WM_CHAR, dbch[0], 0 );
    ok_sequence( WmEmptySeq, "no messages", FALSE );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );
    PostMessageA( hwnd, WM_CHAR, dbch[1], 0 );
    ok_sequence( WmEmptySeq, "no messages", FALSE );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( ret, "no message\n" );
    ok( msg.message == WM_CHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == wch, "bad wparam %lx/%x\n", msg.wParam, wch );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );
    SendMessageA( hwnd, WM_CHAR, dbch[1], 0 );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );

    /* interleaved sent message and winproc */
    flush_sequence();
    SendMessageA( hwnd, WM_CHAR, dbch[0], 0 );
    CallWindowProcA( (WNDPROC)GetWindowLongPtrA( hwnd, GWLP_WNDPROC ), hwnd, WM_CHAR, dbch[0], 0 );
    ok_sequence( WmEmptySeq, "no messages", FALSE );
    SendMessageA( hwnd, WM_CHAR, dbch[1], 0 );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );
    CallWindowProcA( (WNDPROC)GetWindowLongPtrA( hwnd, GWLP_WNDPROC ), hwnd, WM_CHAR, dbch[1], 0 );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );

    /* interleaved winproc and dispatch */
    msg.hwnd = hwnd;
    msg.message = WM_CHAR;
    msg.wParam = dbch[0];
    msg.lParam = 0;
    CallWindowProcA( (WNDPROC)GetWindowLongPtrA( hwnd, GWLP_WNDPROC ), hwnd, WM_CHAR, dbch[0], 0 );
    DispatchMessageA( &msg );
    ok_sequence( WmEmptySeq, "no messages", FALSE );
    msg.wParam = dbch[1];
    DispatchMessageA( &msg );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );
    CallWindowProcA( (WNDPROC)GetWindowLongPtrA( hwnd, GWLP_WNDPROC ), hwnd, WM_CHAR, dbch[1], 0 );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );

    /* interleaved sends */
    flush_sequence();
    SendMessageA( hwnd, WM_CHAR, dbch[0], 0 );
    SendMessageCallbackA( hwnd, WM_CHAR, dbch[0], 0, NULL, 0 );
    ok_sequence( WmEmptySeq, "no messages", FALSE );
    SendMessageTimeoutA( hwnd, WM_CHAR, dbch[1], 0, SMTO_NORMAL, 0, &res );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );
    SendMessageA( hwnd, WM_CHAR, dbch[1], 0 );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );

    /* dbcs WM_CHAR */
    flush_sequence();
    SendMessageA( hwnd2, WM_CHAR, (dbch[1] << 8) | dbch[0], 0 );
    ok_sequence( wmCharSeq, "Unicode WM_CHAR", FALSE );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );

    /* other char messages are not magic */
    PostMessageA( hwnd, WM_SYSCHAR, dbch[0], 0 );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( ret, "no message\n" );
    ok( msg.message == WM_SYSCHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == bad_wch, "bad wparam %lx/%x\n", msg.wParam, bad_wch );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );
    PostMessageA( hwnd, WM_DEADCHAR, dbch[0], 0 );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( ret, "no message\n" );
    ok( msg.message == WM_DEADCHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == bad_wch, "bad wparam %lx/%x\n", msg.wParam, bad_wch );
    ret = PeekMessageW( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );

    /* test retrieving messages */

    PostMessageW( hwnd, WM_CHAR, wch, 0 );
    ret = PeekMessageA( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( ret, "no message\n" );
    ok( msg.hwnd == hwnd, "unexpected hwnd %p\n", msg.hwnd );
    ok( msg.message == WM_CHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == dbch[0], "bad wparam %lx/%x\n", msg.wParam, dbch[0] );
    ret = PeekMessageA( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( ret, "no message\n" );
    ok( msg.hwnd == hwnd, "unexpected hwnd %p\n", msg.hwnd );
    ok( msg.message == WM_CHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == dbch[1], "bad wparam %lx/%x\n", msg.wParam, dbch[0] );
    ret = PeekMessageA( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );

    /* message filters */
    PostMessageW( hwnd, WM_CHAR, wch, 0 );
    ret = PeekMessageA( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( ret, "no message\n" );
    ok( msg.hwnd == hwnd, "unexpected hwnd %p\n", msg.hwnd );
    ok( msg.message == WM_CHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == dbch[0], "bad wparam %lx/%x\n", msg.wParam, dbch[0] );
    /* message id is filtered, hwnd is not */
    ret = PeekMessageA( &msg, hwnd, WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE );
    ok( !ret, "no message\n" );
    ret = PeekMessageA( &msg, hwnd2, 0, 0, PM_REMOVE );
    ok( ret, "no message\n" );
    ok( msg.hwnd == hwnd, "unexpected hwnd %p\n", msg.hwnd );
    ok( msg.message == WM_CHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == dbch[1], "bad wparam %lx/%x\n", msg.wParam, dbch[0] );
    ret = PeekMessageA( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );

    /* mixing GetMessage and PostMessage */
    PostMessageW( hwnd, WM_CHAR, wch, 0xbeef );
    ok( GetMessageA( &msg, hwnd, 0, 0 ), "no message\n" );
    ok( msg.hwnd == hwnd, "unexpected hwnd %p\n", msg.hwnd );
    ok( msg.message == WM_CHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == dbch[0], "bad wparam %lx/%x\n", msg.wParam, dbch[0] );
    ok( msg.lParam == 0xbeef, "bad lparam %lx\n", msg.lParam );
    time = msg.time;
    pt = msg.pt;
    ok( time - GetTickCount() <= 100, "bad time %x\n", msg.time );
    ret = PeekMessageA( &msg, 0, 0, 0, PM_REMOVE );
    ok( ret, "no message\n" );
    ok( msg.hwnd == hwnd, "unexpected hwnd %p\n", msg.hwnd );
    ok( msg.message == WM_CHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == dbch[1], "bad wparam %lx/%x\n", msg.wParam, dbch[0] );
    ok( msg.lParam == 0xbeef, "bad lparam %lx\n", msg.lParam );
    ok( msg.time == time, "bad time %x/%x\n", msg.time, time );
    ok( msg.pt.x == pt.x && msg.pt.y == pt.y, "bad point %u,%u/%u,%u\n", msg.pt.x, msg.pt.y, pt.x, pt.y );
    ret = PeekMessageA( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );

    /* without PM_REMOVE */
    PostMessageW( hwnd, WM_CHAR, wch, 0 );
    ret = PeekMessageA( &msg, 0, 0, 0, PM_NOREMOVE );
    ok( ret, "no message\n" );
    ok( msg.hwnd == hwnd, "unexpected hwnd %p\n", msg.hwnd );
    ok( msg.message == WM_CHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == dbch[0], "bad wparam %lx/%x\n", msg.wParam, dbch[0] );
    ret = PeekMessageA( &msg, 0, 0, 0, PM_REMOVE );
    ok( ret, "no message\n" );
    ok( msg.hwnd == hwnd, "unexpected hwnd %p\n", msg.hwnd );
    ok( msg.message == WM_CHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == dbch[0], "bad wparam %lx/%x\n", msg.wParam, dbch[0] );
    ret = PeekMessageA( &msg, 0, 0, 0, PM_NOREMOVE );
    ok( ret, "no message\n" );
    ok( msg.hwnd == hwnd, "unexpected hwnd %p\n", msg.hwnd );
    ok( msg.message == WM_CHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == dbch[1], "bad wparam %lx/%x\n", msg.wParam, dbch[0] );
    ret = PeekMessageA( &msg, 0, 0, 0, PM_REMOVE );
    ok( ret, "no message\n" );
    ok( msg.hwnd == hwnd, "unexpected hwnd %p\n", msg.hwnd );
    ok( msg.message == WM_CHAR, "unexpected message %x\n", msg.message );
    ok( msg.wParam == dbch[1], "bad wparam %lx/%x\n", msg.wParam, dbch[0] );
    ret = PeekMessageA( &msg, hwnd, 0, 0, PM_REMOVE );
    ok( !ret, "got message %x\n", msg.message );

    DestroyWindow(hwnd);
    DestroyWindow(hwnd2);
}