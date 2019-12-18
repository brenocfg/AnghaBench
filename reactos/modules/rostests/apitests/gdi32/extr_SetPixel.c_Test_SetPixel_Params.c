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
typedef  scalar_t__ HDC ;

/* Variables and functions */
 scalar_t__ CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 scalar_t__ CreateICA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPixel (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int) ; 

void Test_SetPixel_Params()
{
    HDC hdc;

    SetLastError(0);
    ok_long(SetPixel(0, 0, 0, RGB(255,255,255)), -1);
    ok_err(ERROR_INVALID_HANDLE);

    /* Test an info DC */
    hdc = CreateICA("DISPLAY", NULL, NULL, NULL);
    ok(hdc != 0, "\n");
    SetLastError(0);
    ok_long(SetPixel(hdc, 0, 0, 0), -1);
    ok_long(SetPixel(hdc, 0, 0, RGB(255,255,255)), -1);
    ok_err(0);
    DeleteDC(hdc);

    /* Test a mem DC without selecting a bitmap */
    hdc = CreateCompatibleDC(NULL);
    ok(hdc != 0, "\n");
    SetLastError(0);
    ok_long(SetPixel(hdc, 0, 0, 0), -1);
    ok_err(0);
    DeleteDC(hdc);

    /* Test deleted DC */
    ok_long(SetPixel(hdc, 0, 0, 0), -1);

}