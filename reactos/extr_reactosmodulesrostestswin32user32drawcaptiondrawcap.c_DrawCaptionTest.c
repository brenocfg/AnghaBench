#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int bottom; int left; int right; int top; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CapTest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int DC_ACTIVE ; 
 int DC_ICON ; 
 int DC_INBUTTON ; 
 int DC_TEXT ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 

VOID DrawCaptionTest(HWND hWnd, HDC hDc, WCHAR *AddonStr, DWORD Addon)
{
	RECT Rect;
	GetClientRect(hWnd, &Rect);
	Rect.bottom = 30;
	Rect.left = 10;
	Rect.right-=10;
	Rect.top = 10;

	CapTest(hWnd, hDc, &Rect, L"DC_TEXT:", DC_TEXT, AddonStr, Addon);

	CapTest(hWnd, hDc, &Rect,
		L"DC_TEXT | DC_ACTIVE:",
		DC_TEXT | DC_ACTIVE,
		AddonStr, Addon);

	CapTest(hWnd, hDc, &Rect,
		L"DC_TEXT | DC_ICON:" ,
		DC_TEXT | DC_ICON,
		AddonStr, Addon);

	CapTest(hWnd, hDc, &Rect,
		L"DC_TEXT | DC_ACTIVE | DC_ICON:" ,
		DC_TEXT | DC_ACTIVE | DC_ICON,
		AddonStr, Addon);

	CapTest(hWnd, hDc, &Rect,
		L"DC_TEXT | DC_INBUTTON:" ,
		DC_TEXT | DC_INBUTTON,
		AddonStr, Addon);

	CapTest(hWnd, hDc, &Rect,
		L"DC_TEXT | DC_ACTIVE | DC_INBUTTON:" ,
		DC_TEXT | DC_ACTIVE | DC_INBUTTON,
		AddonStr, Addon);

	CapTest(hWnd, hDc, &Rect,
		L"DC_TEXT | DC_ICON | DC_INBUTTON:" ,
		DC_TEXT | DC_ICON | DC_INBUTTON,
		AddonStr, Addon);

	CapTest(hWnd, hDc, &Rect,
		L"DC_TEXT | DC_ACTIVE | DC_ICON | DC_INBUTTON:" ,
		DC_TEXT | DC_ACTIVE | DC_ICON | DC_INBUTTON,
		AddonStr, Addon);

}