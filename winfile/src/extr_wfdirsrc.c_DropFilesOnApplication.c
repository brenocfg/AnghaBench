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
typedef  int WORD ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ CreateDropFiles (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCursorPos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PostMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  PtInRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScreenToClient (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WM_DROPFILES ; 
 int /*<<< orphan*/ * hwndGlobalSink ; 

WORD
DropFilesOnApplication(LPTSTR pszFiles)
{
    POINT pt;
    HWND hwnd;
    RECT rc;
    HANDLE hDrop;

    if (!(hwnd = hwndGlobalSink))
        return 0;

    hwndGlobalSink = NULL;

    GetCursorPos(&pt);
    GetClientRect(hwnd,&rc);
    ScreenToClient(hwnd,&pt);

    hDrop = CreateDropFiles(pt, !PtInRect(&rc,pt), pszFiles);
        
    if (!hDrop)
        return 0;

    PostMessage(hwnd, WM_DROPFILES, (WPARAM)hDrop, 0L);

    return 1;
}