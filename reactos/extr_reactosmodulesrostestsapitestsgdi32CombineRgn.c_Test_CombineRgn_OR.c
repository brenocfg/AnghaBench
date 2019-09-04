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
typedef  int /*<<< orphan*/  HRGN ;

/* Variables and functions */
 int /*<<< orphan*/  COMPLEXREGION ; 
 int /*<<< orphan*/  CombineRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateRectRgn (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  EqualRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGN_OR ; 
 int /*<<< orphan*/  SIMPLEREGION ; 
 int /*<<< orphan*/  SetRectRgn (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Test_CombineRgn_OR()
{
    HRGN hrgn1, hrgn2, hrgn3;

    hrgn1 = CreateRectRgn(0, 0, 0, 0);
    hrgn2 = CreateRectRgn(0, 0, 5, 5);
    hrgn3 = CreateRectRgn(5, 0, 10, 5);
    ok_long(CombineRgn(hrgn1, hrgn2, hrgn3, RGN_OR), SIMPLEREGION);
    SetRectRgn(hrgn2, 0, 0, 10, 5);
    ok(EqualRgn(hrgn1, hrgn2), "Region is not correct\n");

    SetRectRgn(hrgn2, 0, 0, 10, 10);
    SetRectRgn(hrgn3, 10, 10, 20, 20);
    ok_long(CombineRgn(hrgn1, hrgn2, hrgn3, RGN_OR), COMPLEXREGION);
    SetRectRgn(hrgn2, 10, 0, 20, 10);
    ok_long(CombineRgn(hrgn1, hrgn1, hrgn2, RGN_OR), COMPLEXREGION);
    ok_long(CombineRgn(hrgn1, hrgn1, hrgn1, RGN_OR), COMPLEXREGION);
    SetRectRgn(hrgn2, 0, 10, 10, 20);
    ok_long(CombineRgn(hrgn1, hrgn1, hrgn2, RGN_OR), SIMPLEREGION);
    SetRectRgn(hrgn2, 0, 0, 20, 20);
    ok(EqualRgn(hrgn1, hrgn2), "Region is not correct\n");

}