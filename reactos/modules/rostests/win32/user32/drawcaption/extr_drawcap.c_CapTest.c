#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int top; int bottom; } ;
typedef  TYPE_1__* LPRECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DT_LEFT ; 
 int /*<<< orphan*/  DrawCaption (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  DrawText (int /*<<< orphan*/ ,char*,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  lstrcat (char*,char*) ; 
 int /*<<< orphan*/  lstrcpy (char*,char*) ; 
 scalar_t__ lstrlen (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

VOID CapTest(HWND hWnd,
	HDC hDc,
	LPRECT pR,
	WCHAR *Text,
	DWORD Flags,
	WCHAR *AddonStr,
	DWORD Addon)
{
	WCHAR Buf[512];

	lstrcpy(Buf, AddonStr);
	if(lstrlen(Buf))lstrcat(Buf, L" | ");
	lstrcat(Buf, Text);

	DrawText( hDc, Buf, lstrlen(Buf), pR, DT_LEFT );

	pR->top+=20;
	pR->bottom+=20;

	if(!DrawCaption(hWnd, hDc, pR, Flags | Addon))
	{
		printf("PAINT: DrawCaption failed: %d\n", (int)GetLastError());
	}

	pR->top+=30;
	pR->bottom+=30;
}