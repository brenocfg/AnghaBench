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
typedef  char WCHAR ;
struct TYPE_2__ {char num_sep; int /*<<< orphan*/  spaceSize; int /*<<< orphan*/  hfont; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetNumberFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GetTextExtentPoint32W (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_1__ Globals ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sSpace ; 

__attribute__((used)) static void init_output(HWND hwnd)
{
	static const WCHAR s1000[] = {'1','0','0','0','\0'};
	WCHAR b[16];
	HFONT old_font;
	HDC hdc = GetDC(hwnd);

	if (GetNumberFormatW(LOCALE_USER_DEFAULT, 0, s1000, 0, b, 16) > 4)
		Globals.num_sep = b[1];
	else
		Globals.num_sep = '.';

	old_font = SelectObject(hdc, Globals.hfont);
	GetTextExtentPoint32W(hdc, sSpace, 1, &Globals.spaceSize);
	SelectObject(hdc, old_font);
	ReleaseDC(hwnd, hdc);
}