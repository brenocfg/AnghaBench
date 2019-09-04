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
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SPY_DumpStructure (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPY_GetMsgStuff (TYPE_1__*) ; 
 int /*<<< orphan*/  SPY_GetWndName (TYPE_1__*) ; 
 scalar_t__ SPY_INDENT_UNIT ; 
#define  SPY_RESULT_DEFWND 129 
#define  SPY_RESULT_OK 128 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 scalar_t__ exclude_dwp () ; 
 scalar_t__ exclude_msg (int /*<<< orphan*/ ) ; 
 int get_indent_level () ; 
 int /*<<< orphan*/  message ; 
 int /*<<< orphan*/  set_indent_level (int) ; 

void SPY_ExitMessage( INT iFlag, HWND hWnd, UINT msg, LRESULT lReturn,
                       WPARAM wParam, LPARAM lParam )
{
    SPY_INSTANCE sp_e;
    int indent;
    DWORD save_error = GetLastError();

    if (!TRACE_ON(message) || exclude_msg(msg) ||
        (exclude_dwp() && iFlag == SPY_RESULT_DEFWND))
        return;

    sp_e.msgnum = msg;
    sp_e.msg_hwnd   = hWnd;
    sp_e.lParam = lParam;
    sp_e.wParam = wParam;
    SPY_GetWndName(&sp_e);
    SPY_GetMsgStuff(&sp_e);

    if ((indent = get_indent_level()))
    {
        indent -= SPY_INDENT_UNIT;
        set_indent_level( indent );
    }

    switch(iFlag)
    {
    case SPY_RESULT_DEFWND:
        TRACE(" %*s(%p)  DefWindowProc: [%04x] %s returned %08lx\n",
              indent, "", hWnd, msg, sp_e.msg_name, lReturn );
        break;

    case SPY_RESULT_OK:
        TRACE(" %*s(%p) %-16s [%04x] %s returned %08lx\n",
                        indent, "", hWnd, debugstr_w(sp_e.wnd_name), msg,
                        sp_e.msg_name, lReturn );
        SPY_DumpStructure(&sp_e, FALSE);
        break;
    }
    SetLastError( save_error );
}