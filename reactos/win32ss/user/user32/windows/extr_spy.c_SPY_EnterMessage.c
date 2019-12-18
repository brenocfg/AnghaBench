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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/  msg_name; int /*<<< orphan*/  wnd_name; int /*<<< orphan*/  wParam; int /*<<< orphan*/  lParam; int /*<<< orphan*/  msg_hwnd; int /*<<< orphan*/  msgnum; } ;
typedef  TYPE_1__ SPY_INSTANCE ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetWindowThreadProcessId (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  SPY_DEFWNDPROC 130 
#define  SPY_DISPATCHMESSAGE 129 
 int /*<<< orphan*/  SPY_DumpStructure (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPY_GetMsgStuff (TYPE_1__*) ; 
 int /*<<< orphan*/  SPY_GetWndName (TYPE_1__*) ; 
 scalar_t__ SPY_INDENT_UNIT ; 
#define  SPY_SENDMESSAGE 128 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exclude_dwp () ; 
 scalar_t__ exclude_msg (int /*<<< orphan*/ ) ; 
 int get_indent_level () ; 
 int /*<<< orphan*/  set_indent_level (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spy_init () ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void SPY_EnterMessage( INT iFlag, HWND hWnd, UINT msg,
                       WPARAM wParam, LPARAM lParam )
{
    SPY_INSTANCE sp_e;
    int indent;
    DWORD save_error = GetLastError();

    if (!spy_init() || exclude_msg(msg)) return;

    sp_e.msgnum = msg;
    sp_e.msg_hwnd = hWnd;
    sp_e.lParam = lParam;
    sp_e.wParam = wParam;
    SPY_GetWndName(&sp_e);
    SPY_GetMsgStuff(&sp_e);
    indent = get_indent_level();

    /* each SPY_SENDMESSAGE must be complemented by call to SPY_ExitMessage */
    switch(iFlag)
    {
    case SPY_DISPATCHMESSAGE:
        TRACE("%*s(%p) %-16s [%04x] %s dispatched  wp=%08lx lp=%08lx\n",
                        indent, "", hWnd, debugstr_w(sp_e.wnd_name), msg,
                        sp_e.msg_name, wParam, lParam);
        break;

    case SPY_SENDMESSAGE:
        {
            char taskName[20];
            DWORD tid = GetWindowThreadProcessId( hWnd, NULL );

            if (tid == GetCurrentThreadId()) strcpy( taskName, "self" );
            else sprintf( taskName, "tid %04ld", GetCurrentThreadId() );

            TRACE("%*s(%p) %-16s [%04x] %s sent from %s wp=%08lx lp=%08lx\n",
                  indent, "", hWnd, debugstr_w(sp_e.wnd_name), msg,
                  sp_e.msg_name, taskName, wParam, lParam );
            SPY_DumpStructure(&sp_e, TRUE);
        }
        break;

    case SPY_DEFWNDPROC:
        if (exclude_dwp()) return;
        TRACE("%*s(%p)  DefWindowProc:[%04x] %s  wp=%08lx lp=%08lx\n",
              indent, "", hWnd, msg, sp_e.msg_name, wParam, lParam );
        break;
    }
    set_indent_level( indent + SPY_INDENT_UNIT );
    SetLastError( save_error );
}