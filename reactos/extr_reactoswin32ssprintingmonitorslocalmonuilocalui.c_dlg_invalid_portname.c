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
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IDS_INVALIDNAME ; 
 int IDS_INVALIDNAME_MAXLEN ; 
 int /*<<< orphan*/  IDS_LOCALPORT ; 
 int IDS_LOCALPORT_MAXLEN ; 
 int /*<<< orphan*/  LOCALUI_hInstance ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int MB_ICONERROR ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ ,char*,char*,int) ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintfW (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dlg_invalid_portname(HWND hWnd, LPCWSTR portname)
{
    WCHAR res_PortW[IDS_LOCALPORT_MAXLEN];
    WCHAR res_InvalidNameW[IDS_INVALIDNAME_MAXLEN];
    LPWSTR  message;
    DWORD   len;

    res_PortW[0] = '\0';
    res_InvalidNameW[0] = '\0';
    LoadStringW(LOCALUI_hInstance, IDS_LOCALPORT, res_PortW, IDS_LOCALPORT_MAXLEN);
    LoadStringW(LOCALUI_hInstance, IDS_INVALIDNAME, res_InvalidNameW, IDS_INVALIDNAME_MAXLEN);

    len = lstrlenW(portname) + IDS_INVALIDNAME_MAXLEN;
    message = HeapAlloc(GetProcessHeap(), 0, len * sizeof(WCHAR));
    if (message) {
        message[0] = '\0';
        snprintfW(message, len, res_InvalidNameW, portname);
        MessageBoxW(hWnd, message, res_PortW, MB_OK | MB_ICONERROR);
        HeapFree(GetProcessHeap(), 0, message);
    }
}