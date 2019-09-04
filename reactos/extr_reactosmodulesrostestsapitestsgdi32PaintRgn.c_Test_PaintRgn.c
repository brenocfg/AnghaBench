#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double eM11; float eM12; double eM21; double eM22; double eDx; double eDy; } ;
typedef  TYPE_1__ XFORM ;
struct TYPE_6__ {int member_2; int member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int /*<<< orphan*/ * HRGN ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_BRUSH ; 
 int /*<<< orphan*/  CombineRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateRectRgn (int,int,int,int) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GM_ADVANCED ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 scalar_t__ PaintRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RGN_OR ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetGraphicsMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SetWorldTransform (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WHITE_BRUSH ; 
 int /*<<< orphan*/  ghdcDIB1 ; 
 int /*<<< orphan*/ * gpvDIB1 ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int) ; 

void Test_PaintRgn()
{
    RECT rc = { 0, 0, 100, 100 };
    HRGN hrgn1, hrgn2;
    BOOL bRet;
    XFORM xform;
    PULONG pulDIB = gpvDIB1;

    FillRect(ghdcDIB1, &rc, GetStockObject(BLACK_BRUSH));

    hrgn1 = CreateRectRgn(0, 0, 8, 3);
    ok(hrgn1 != NULL, "failed to create region\n");

    hrgn2 = CreateRectRgn(2, 3, 5, 8);
    ok(hrgn1 != NULL, "failed to create region\n");

    CombineRgn(hrgn1, hrgn1, hrgn2, RGN_OR);

    xform.eM11 = 1.0;
    xform.eM12 = 0.5f;
    xform.eM21 = 0.0;
    xform.eM22 = 1.0;
    xform.eDx = 0.0;
    xform.eDy = 0.0;

    SetGraphicsMode(ghdcDIB1, GM_ADVANCED);
    ok(SetWorldTransform(ghdcDIB1, &xform) == TRUE, "SetWorldTransform failed\n");

    SelectObject(ghdcDIB1, GetStockObject(WHITE_BRUSH));

    bRet = PaintRgn(ghdcDIB1, hrgn1);
    ok(bRet == TRUE, "PaintRgn failed\n");

    ok_long(pulDIB[0], 0x00000000); // 000000000
    ok_long(pulDIB[1], 0x000000C0); // 110000000
    ok_long(pulDIB[2], 0x000000F0); // 111110000
    ok_long(pulDIB[3], 0x000000FC); // 111111000
    ok_long(pulDIB[4], 0x0000003F); // 001111110
    ok_long(pulDIB[5], 0x0000003F); // 001111110
    ok_long(pulDIB[6], 0x0000003B); // 001110110
    ok_long(pulDIB[7], 0x00000038); // 001110000
    ok_long(pulDIB[8], 0x00000038); // 001110000
}