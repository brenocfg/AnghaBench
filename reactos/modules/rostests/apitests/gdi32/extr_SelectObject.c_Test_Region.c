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
typedef  scalar_t__ UINT_PTR ;
typedef  scalar_t__ HRGN ;

/* Variables and functions */
 scalar_t__ COMPLEXREGION ; 
 scalar_t__ CombineRgn (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateRectRgn (int,int,int,int) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ NULLREGION ; 
 int /*<<< orphan*/  RGN_OR ; 
 scalar_t__ SIMPLEREGION ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdc1 ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_err (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
Test_Region()
{
    HRGN hrgn, hrgnOld;

	/* Test REGION */
	SetLastError(ERROR_SUCCESS);
	hrgn = CreateRectRgn(0,0,0,0);
	hrgnOld = SelectObject(hdc1, hrgn);
	ok((UINT_PTR)hrgnOld == NULLREGION, "\n");
	DeleteObject(hrgn);

	hrgn = CreateRectRgn(0,0,10,10);
	ok((UINT_PTR)SelectObject(hdc1, hrgn) == SIMPLEREGION, "\n");
	hrgnOld = CreateRectRgn(5,5,20,20);
	ok(CombineRgn(hrgn, hrgn, hrgnOld, RGN_OR) == COMPLEXREGION, "\n");
	DeleteObject(hrgnOld);
	ok((UINT_PTR)SelectObject(hdc1, hrgn) == SIMPLEREGION, "\n"); // ??? Why this?
	DeleteObject(hrgn);
//	ok(IsHandleValid(hrgn) == TRUE, "\n");
	ok_err(ERROR_SUCCESS);
}