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
typedef  float WCHAR ;
typedef  int /*<<< orphan*/  IFileDialog ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  CB_SHOWDROPDOWN ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WM_LBUTTONDOWN ; 
 int /*<<< orphan*/  WM_LBUTTONUP ; 
 int broken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_window (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float const*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void filedialog_change_filetype(IFileDialog *pfd, HWND dlg_hwnd)
{
    HWND cb_filetype;
    const WCHAR filetype1[] = {'f','n','a','m','e','1',0};
    const WCHAR filetype1_broken[] = {'f','n','a','m','e','1',' ', '(','*','.','t','x','t',')',0};

    cb_filetype = find_window(dlg_hwnd, NULL, filetype1);
    ok(cb_filetype != NULL || broken(cb_filetype == NULL), "Could not find combobox on first attempt\n");

    if(!cb_filetype)
    {
        /* Not sure when this happens. Some specific version?
         * Seen on 32-bit English Vista */
        trace("Didn't find combobox on first attempt, trying broken string..\n");
        cb_filetype = find_window(dlg_hwnd, NULL, filetype1_broken);
        ok(broken(cb_filetype != NULL), "Failed to find combobox on second attempt\n");
        if(!cb_filetype)
            return;
    }

    /* Making the combobox send a CBN_SELCHANGE */
    SendMessageW( cb_filetype, CB_SHOWDROPDOWN, 1, 0 );
    SendMessageW( cb_filetype, CB_SETCURSEL, 1, 0 );
    SendMessageW( cb_filetype, WM_LBUTTONDOWN, 0, -1 );
    SendMessageW( cb_filetype, WM_LBUTTONUP, 0, -1 );
}