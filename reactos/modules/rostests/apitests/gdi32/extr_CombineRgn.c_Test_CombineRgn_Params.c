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
typedef  int /*<<< orphan*/ * HRGN ;

/* Variables and functions */
 int /*<<< orphan*/  CombineRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * CreateRectRgn (int,int,int,int) ; 
 int /*<<< orphan*/  ERROR ; 
 int ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Test_CombineRgn_Params()
{
    HRGN hrgn1, hrgn2, hrgn3;

    hrgn1 = CreateRectRgn(0, 0, 0, 0);
    hrgn2 = CreateRectRgn(0, 0, 10, 10);
    hrgn3 = CreateRectRgn(5, 5, 20, 20);

    SetLastError(0xbadbabe);
    ok_long(CombineRgn(NULL, NULL, NULL, 0), ERROR);
    ok_long(CombineRgn(hrgn1, hrgn2, hrgn3, 0), ERROR);
    ok_long(CombineRgn(hrgn1, hrgn2, hrgn3, 6), ERROR);
    ok((GetLastError() == 0xbadbabe) || (GetLastError() == ERROR_INVALID_PARAMETER), "wrong error: %ld\n", GetLastError());

}