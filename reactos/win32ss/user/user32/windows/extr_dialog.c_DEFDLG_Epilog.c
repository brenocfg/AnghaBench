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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  scalar_t__ UINT ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DWLP_MSGRESULT ; 
 scalar_t__ DefWindowProcA (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DefWindowProcW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WM_CHARTOITEM ; 
 scalar_t__ WM_COMPAREITEM ; 
 scalar_t__ WM_CTLCOLOR ; 
 scalar_t__ WM_CTLCOLORMSGBOX ; 
 scalar_t__ WM_CTLCOLORSTATIC ; 
 scalar_t__ WM_INITDIALOG ; 
 scalar_t__ WM_QUERYDRAGICON ; 
 scalar_t__ WM_VKEYTOITEM ; 

__attribute__((used)) static LRESULT DEFDLG_Epilog(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, BOOL fResult, BOOL fAnsi)
{
    if ((msg >= WM_CTLCOLORMSGBOX && msg <= WM_CTLCOLORSTATIC) ||
         msg == WM_CTLCOLOR)
       {
          if (fResult) return fResult;

          return fAnsi ? DefWindowProcA(hwnd, msg, wParam, lParam):
                         DefWindowProcW(hwnd, msg, wParam, lParam);
       }
    if ( msg == WM_COMPAREITEM ||
         msg == WM_VKEYTOITEM || msg == WM_CHARTOITEM ||
         msg == WM_QUERYDRAGICON || msg == WM_INITDIALOG)
        return fResult;

    return GetWindowLongPtrW( hwnd, DWLP_MSGRESULT );
}