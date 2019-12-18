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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindow (char*,char const*,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  g_hInst ; 
 int /*<<< orphan*/  g_hwnd ; 
 int /*<<< orphan*/ * g_hwndCtrl ; 
 int nMaxCtrls ; 
 int /*<<< orphan*/  nNextCtrl ; 
 int nStaticHeight ; 
 int /*<<< orphan*/  nStaticWidth ; 

__attribute__((used)) static void CreateStatic ( const char* lpWindowName, DWORD dwStyle )
{
	int n = nNextCtrl++;
	assert ( n < nMaxCtrls );
	g_hwndCtrl[n] = CreateWindow (
		"STATIC", // lpClassName
		lpWindowName, // lpWindowName
		WS_VISIBLE|WS_CHILD|dwStyle, // dwStyle
		n+2, // x
		nStaticHeight*n+1, // y
		nStaticWidth, // nWidth
		nStaticHeight-1, // nHeight
		g_hwnd, // hWndParent
		NULL, // hMenu
		g_hInst, // hInstance
		NULL ); // lParam
}