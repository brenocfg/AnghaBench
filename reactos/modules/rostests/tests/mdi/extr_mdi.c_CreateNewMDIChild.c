#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* szTitle; int /*<<< orphan*/  style; void* cy; void* y; void* cx; void* x; int /*<<< orphan*/  hOwner; int /*<<< orphan*/  szClass; } ;
typedef  TYPE_1__ MDICREATESTRUCT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 void* CW_USEDEFAULT ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int MB_ICONEXCLAMATION ; 
 int MB_OK ; 
 int /*<<< orphan*/  MDIS_ALLCHILDSTYLES ; 
 int /*<<< orphan*/  MessageBox (scalar_t__,char*,char*,int) ; 
 scalar_t__ SendMessage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_MDICREATE ; 
 int /*<<< orphan*/  g_szChildClassName ; 

HWND CreateNewMDIChild(HWND hMDIClient)
{
	MDICREATESTRUCT mcs;
	HWND hChild;

	mcs.szTitle = "[Untitled]";
	mcs.szClass = g_szChildClassName;
	mcs.hOwner  = GetModuleHandle(NULL);
	mcs.x = mcs.cx = CW_USEDEFAULT;
	mcs.y = mcs.cy = CW_USEDEFAULT;
	mcs.style = MDIS_ALLCHILDSTYLES;

	hChild = (HWND)SendMessage(hMDIClient, WM_MDICREATE, 0, (LPARAM)&mcs);
	if(!hChild)
	{
		MessageBox(hMDIClient, "MDI Child creation failed.", "Oh Oh...",
			MB_ICONEXCLAMATION | MB_OK);
	}
	return hChild;
}