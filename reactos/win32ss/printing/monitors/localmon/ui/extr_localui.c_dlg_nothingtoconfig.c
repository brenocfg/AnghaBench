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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  IDS_LOCALPORT ; 
 int IDS_LOCALPORT_MAXLEN ; 
 int /*<<< orphan*/  IDS_NOTHINGTOCONFIG ; 
 int IDS_NOTHINGTOCONFIG_MAXLEN ; 
 int /*<<< orphan*/  LOCALUI_hInstance ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int MB_ICONINFORMATION ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static void dlg_nothingtoconfig(HWND hWnd)
{
    WCHAR res_PortW[IDS_LOCALPORT_MAXLEN];
    WCHAR res_nothingW[IDS_NOTHINGTOCONFIG_MAXLEN];

    res_PortW[0] = '\0';
    res_nothingW[0] = '\0';
    LoadStringW(LOCALUI_hInstance, IDS_LOCALPORT, res_PortW, IDS_LOCALPORT_MAXLEN);
    LoadStringW(LOCALUI_hInstance, IDS_NOTHINGTOCONFIG, res_nothingW, IDS_NOTHINGTOCONFIG_MAXLEN);

    MessageBoxW(hWnd, res_nothingW, res_PortW, MB_OK | MB_ICONINFORMATION);
}