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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DoTest1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DoTest2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DoTest3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  IDC_END 131 
#define  IDC_TEST1 130 
#define  IDC_TEST2 129 
#define  IDC_TEST3 128 
 int /*<<< orphan*/  IDOK ; 
 int /*<<< orphan*/  MAKEWPARAM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_COMMAND ; 

__attribute__((used)) static void
OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
        case IDC_TEST1:
            DoTest1(hwnd);
            PostMessage(hwnd, WM_COMMAND, MAKEWPARAM(IDC_TEST2, 0), 0);
            break;
        case IDC_TEST2:
            DoTest2(hwnd);
            PostMessage(hwnd, WM_COMMAND, MAKEWPARAM(IDC_TEST3, 0), 0);
            break;
        case IDC_TEST3:
            DoTest3(hwnd);
            PostMessage(hwnd, WM_COMMAND, MAKEWPARAM(IDC_END, 0), 0);
            break;
        case IDC_END:
            EndDialog(hwnd, IDOK);
            break;
    }
}