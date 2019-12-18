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
typedef  int /*<<< orphan*/ * HDC ;
typedef  scalar_t__ HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_PEN ; 
 int CLR_INVALID ; 
 scalar_t__ CreateBitmap (int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DC_PEN ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int GetPixel (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int RGB (int,int,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ *,scalar_t__) ; 
 int SetDCPenColor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

void Test_SetDCPenColor()
{
	HDC hScreenDC, hDC;
	HBITMAP hbmp, hbmpOld;

	// Test an incorrect DC
	SetLastError(ERROR_SUCCESS);
	ok(SetDCPenColor(0, RGB(0,0,0)) == CLR_INVALID, "\n");
	ok(GetLastError() == ERROR_INVALID_PARAMETER, "\n");

	// Get the Screen DC
	hScreenDC = GetDC(NULL);
	ok(hScreenDC != 0, "GetDC failed, skipping tests\n");
	if (hScreenDC == NULL) return;

	// Test the screen DC
	SetDCPenColor(hScreenDC, RGB(1,2,3));
	ok(SetDCPenColor(hScreenDC, RGB(4,5,6)) == RGB(1,2,3), "\n");

	// Create a new DC
	hDC = CreateCompatibleDC(hScreenDC);
	ReleaseDC(0, hScreenDC);
	ok(hDC != 0, "CreateCompatibleDC failed, skipping tests\n");
	if (!hDC) return;

	// Select the DC_PEN and check if the pen returned by a new call is DC_PEN
	SelectObject(hDC, GetStockObject(DC_PEN));
	ok(SelectObject(hDC, GetStockObject(BLACK_PEN)) == GetStockObject(DC_PEN), "\n");

	// Test an incorrect color, yes windows sets the color!
	SetDCPenColor(hDC, 0x21123456);
	ok(SetDCPenColor(hDC, RGB(0,0,0)) == 0x21123456, "\n");

	// Test CLR_INVALID, it sets CLR_INVALID!
	SetDCPenColor(hDC, CLR_INVALID);
	ok(SetDCPenColor(hDC, RGB(0,0,0)) == CLR_INVALID, "\n");

	hbmp = CreateBitmap(10, 10, 1, 32, NULL);
	ok(hbmp != 0, "CreateBitmap failed, skipping tests\n");
	if (!hbmp) return;
	hbmpOld = SelectObject(hDC, hbmp);
#if 0 // this only works on 32 bpp screen resolution
	ok(hbmpOld != NULL, "\n");
	SelectObject(hDC, GetStockObject(DC_PEN));
	SetDCPenColor(hDC, 0x123456);
	MoveToEx(hDC, 0, 0, NULL);
	LineTo(hDC, 10, 0);
	ok(GetPixel(hDC, 5, 0) == 0x123456, "\n");
#endif

	// Delete the DC
	SelectObject(hDC, hbmpOld);
	DeleteDC(hDC);
}