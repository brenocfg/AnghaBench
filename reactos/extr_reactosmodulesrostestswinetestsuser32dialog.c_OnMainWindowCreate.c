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
typedef  int /*<<< orphan*/  LPCREATESTRUCTA ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BS_DEFPUSHBUTTON ; 
 int BS_PUSHBUTTON ; 
 int BS_TEXT ; 
 void* CreateWindowA (char*,char*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IDCANCEL ; 
 int /*<<< orphan*/  TRUE ; 
 int WS_CHILD ; 
 int WS_TABSTOP ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  g_hinst ; 
 void* g_hwndButton1 ; 
 void* g_hwndButton2 ; 
 void* g_hwndButtonCancel ; 

__attribute__((used)) static BOOL OnMainWindowCreate(HWND hwnd, LPCREATESTRUCTA lpcs)
{
    g_hwndButton1 = CreateWindowA("button", "Button &1",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON | BS_TEXT,
            10, 10, 80, 80, hwnd, (HMENU)100, g_hinst, 0);
    if (!g_hwndButton1) return FALSE;

    g_hwndButton2 = CreateWindowA("button", "Button &2",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_TEXT,
            110, 10, 80, 80, hwnd, (HMENU)200, g_hinst, 0);
    if (!g_hwndButton2) return FALSE;

    g_hwndButtonCancel = CreateWindowA("button", "Cancel",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON | BS_TEXT,
            210, 10, 80, 80, hwnd, (HMENU)IDCANCEL, g_hinst, 0);
    if (!g_hwndButtonCancel) return FALSE;

    return TRUE;
}