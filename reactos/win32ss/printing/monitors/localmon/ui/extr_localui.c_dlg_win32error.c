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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 scalar_t__ FormatMessageW (int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDS_LOCALPORT ; 
 int IDS_LOCALPORT_MAXLEN ; 
 int /*<<< orphan*/  LOCALUI_hInstance ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int MB_ICONERROR ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void dlg_win32error(HWND hWnd, DWORD lasterror)
{
    WCHAR res_PortW[IDS_LOCALPORT_MAXLEN];
    LPWSTR  message = NULL;
    DWORD   res;

    res_PortW[0] = '\0';
    LoadStringW(LOCALUI_hInstance, IDS_LOCALPORT, res_PortW, IDS_LOCALPORT_MAXLEN);


    res = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                        NULL, lasterror, 0, (LPWSTR) &message, 0, NULL);

    if (res > 0) {
        MessageBoxW(hWnd, message, res_PortW, MB_OK | MB_ICONERROR);
        LocalFree(message);
    }
}