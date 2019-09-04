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
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int BS_AUTOCHECKBOX ; 
 int /*<<< orphan*/  CreateWindowEx (int /*<<< orphan*/ ,char*,char const*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UlongToHandle (int /*<<< orphan*/ ) ; 
 int WS_CHILD ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  g_hInst ; 
 int /*<<< orphan*/  g_hwnd ; 
 int /*<<< orphan*/  xButPos ; 
 int yButPos ; 

HWND
CreateCheckButton(const char* lpWindowName, DWORD xSize, DWORD id)
    {
    	HWND h;
 	h  = CreateWindowEx(0,
			  "BUTTON",
                          lpWindowName,
			  WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			  xButPos, /*  x  */
		          yButPos, /*  y  */
		          xSize,   /* nWidth  */
		          20,      /* nHeight */
			  g_hwnd,
			  UlongToHandle(id),
			  g_hInst,
			  NULL
                         );
    	yButPos += 21;
	return h;
    }