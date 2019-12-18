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
 int /*<<< orphan*/  EN_CHANGE ; 
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
#define  IDCANCEL 130 
#define  IDOK 129 
 int /*<<< orphan*/  PropSheet_Changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
#define  edt1 128 
 int /*<<< orphan*/  s_bNotified ; 

__attribute__((used)) static void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
        case IDOK:
        case IDCANCEL:
            EndDialog(hwnd, id);
            break;
        case edt1:
            if (codeNotify == EN_CHANGE)
            {
                s_bNotified = TRUE;
                PropSheet_Changed(GetParent(hwnd), hwnd);
            }
            break;
    }
}