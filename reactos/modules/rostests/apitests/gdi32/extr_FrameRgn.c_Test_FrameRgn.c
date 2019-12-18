#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UCHAR ;
struct TYPE_3__ {int member_2; int member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/ * HRGN ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_BRUSH ; 
 int /*<<< orphan*/  CheckBitmapBits (int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CombineRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateRectRgn (int,int,int,int) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ FillRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FrameRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GRAY_BRUSH ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  RGN_OR ; 
 int /*<<< orphan*/  WHITE_BRUSH ; 
 int /*<<< orphan*/  ghdcDIB32 ; 
 int /*<<< orphan*/  ok (int,char*) ; 

void Test_FrameRgn()
{
    RECT rc = {0, 0, 8, 8 };
    HRGN hrgn1, hrgn2;
    BOOL bRet;
    UCHAR ajBits[64] = {
        0, 0, 0, 0, 0, 0, 0, 0, // 0000000
        0, 1, 1, 1, 1, 0, 0, 0, // 0****00
        0, 1, 2, 2, 1, 0, 0, 0, // 0*xx**0
        0, 1, 2, 2, 1, 1, 1, 0, // 0*xxx*0
        0, 1, 1, 1, 2, 2, 1, 0, // 0**xx*0
        0, 0, 0, 1, 2, 2, 1, 0, // 00****0
        0, 0, 0, 1, 1, 1, 1, 0, // 0000000
        0, 0, 0, 0, 0, 0, 0, 0  // 0000000
    };
    COLORREF acrColors[16] = {RGB(0,0,0), RGB(255,255,255), RGB(128,128,128), 0};

    FillRect(ghdcDIB32, &rc, GetStockObject(BLACK_BRUSH));

    hrgn1 = CreateRectRgn(1, 1, 5, 5);
    ok(hrgn1 != NULL, "failed to create region\n");

    hrgn2 = CreateRectRgn(3, 3, 7, 7);
    ok(hrgn1 != NULL, "failed to create region\n");

    CombineRgn(hrgn1, hrgn1, hrgn2, RGN_OR);

    bRet = FillRgn(ghdcDIB32, hrgn1, GetStockObject(GRAY_BRUSH));
    ok(bRet != 0, "FrameRgn failed\n");

    bRet = FrameRgn(ghdcDIB32, hrgn1, GetStockObject(WHITE_BRUSH), 1, 1);
    ok(bRet != 0, "FrameRgn failed\n");

    CheckBitmapBits(ghdcDIB32, 8, 8, ajBits, acrColors);

}