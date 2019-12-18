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
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int DWORD ;

/* Variables and functions */
 int BS_PUSHBUTTON ; 
 int /*<<< orphan*/  CreateWindow (char*,char const*,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int WS_CHILD ; 
 int /*<<< orphan*/  g_hInst ; 
 int /*<<< orphan*/  g_hwnd ; 
 int /*<<< orphan*/  xButPos ; 
 int yButPos ; 

HWND
CreatePushButton(const char* lpWindowName, DWORD xSize, DWORD id,DWORD Style)
    {

    HWND h = CreateWindow("BUTTON",
                          lpWindowName,
                          WS_CHILD | BS_PUSHBUTTON | Style,
					      xButPos, // x
		                  yButPos, // y
		                  xSize,   // nWidth
		                  20,      // nHeight
					      g_hwnd,
                          (HMENU)(ULONG_PTR) id,
                          g_hInst,
                          NULL
                          );

    yButPos += 21;
    return h;
    }