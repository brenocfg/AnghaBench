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
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_3__ {short x; short y; } ;
typedef  TYPE_1__ POINT ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DefWndTrackScrollBar (int /*<<< orphan*/ ,int,TYPE_1__) ; 
 int /*<<< orphan*/  DoAppSwitch (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  FNID_DEFWINDOWPROC ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ ISITHOOKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindowEnabled (int /*<<< orphan*/ ) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtUserMessageCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SC_CLOSE 142 
#define  SC_HOTKEY 141 
#define  SC_HSCROLL 140 
#define  SC_KEYMENU 139 
#define  SC_MAXIMIZE 138 
#define  SC_MINIMIZE 137 
#define  SC_MOUSEMENU 136 
#define  SC_MOVE 135 
#define  SC_NEXTWINDOW 134 
#define  SC_PREVWINDOW 133 
#define  SC_RESTORE 132 
#define  SC_SCREENSAVE 131 
#define  SC_SIZE 130 
#define  SC_TASKLIST 129 
#define  SC_VSCROLL 128 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int /*<<< orphan*/  WH_CBT ; 
 int /*<<< orphan*/  WM_SYSCOMMAND ; 
 int /*<<< orphan*/  WinExec (char*,int /*<<< orphan*/ ) ; 

LRESULT
DefWndHandleSysCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
  POINT Pt;
  LRESULT lResult;

  if (!IsWindowEnabled( hWnd )) return 0;

  switch (wParam & 0xfff0)
    {
      case SC_MOVE:
      case SC_SIZE:
//      case SC_DEFAULT:
      case SC_MOUSEMENU:
      case SC_KEYMENU:
      case SC_SCREENSAVE:
      case SC_MINIMIZE:
      case SC_MAXIMIZE:
      case SC_RESTORE:
      case SC_CLOSE:
      case SC_HOTKEY:
        NtUserMessageCall( hWnd, WM_SYSCOMMAND, wParam, lParam, (ULONG_PTR)&lResult, FNID_DEFWINDOWPROC, FALSE);
        return 0;

      default:
        break;
    }

  if (ISITHOOKED(WH_CBT))
  {
     NtUserMessageCall( hWnd, WM_SYSCOMMAND, wParam, lParam, (ULONG_PTR)&lResult, FNID_DEFWINDOWPROC, FALSE);
     if (lResult) return 0;
  }

  switch (wParam & 0xfff0)
    {

      case SC_VSCROLL:
      case SC_HSCROLL:
        {
          Pt.x = (short)LOWORD(lParam);
          Pt.y = (short)HIWORD(lParam);
          DefWndTrackScrollBar(hWnd, wParam, Pt);
        }
	break;

      case SC_TASKLIST:
        WinExec( "taskman.exe", SW_SHOWNORMAL );
        break;


      case SC_NEXTWINDOW:
      case SC_PREVWINDOW:
        DoAppSwitch( wParam, lParam);
        break;

      default:
        FIXME("Unimplemented DefWndHandleSysCommand wParam 0x%x\n",wParam);
        break;
    }

  return(0);
}