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
struct TYPE_3__ {int eM11; int eM22; scalar_t__ eDy; scalar_t__ eDx; scalar_t__ eM21; scalar_t__ eM12; } ;
typedef  TYPE_1__ XFORM ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GM_ADVANCED ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetGraphicsMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SetWorldTransform (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

void Test_SetWorldTransform()
{
	HDC hdcScreen, hdc;
	XFORM xform;
	BOOL result;
	//PGDI_TABLE_ENTRY pEntry;
	//DC_ATTR* pdcattr;

	/* Create a DC */
	hdcScreen = GetDC(NULL);
	hdc = CreateCompatibleDC(hdcScreen);
	ReleaseDC(NULL, hdcScreen);
	SetGraphicsMode(hdc, GM_ADVANCED);

    /* Set identity transform */
    xform.eM11 = 1;
    xform.eM12 = 0;
    xform.eM21 = 0;
    xform.eM22 = 1;
    xform.eDx = 0;
    xform.eDy = 0;
    result = SetWorldTransform(hdc, &xform);
    ok(result == 1, "\n");

    /* Something invalid */
    xform.eM22 = 0;
    result = SetWorldTransform(hdc, &xform);
    ok(result == 0, "\n");

	//pEntry = GdiHandleTable + GDI_HANDLE_GET_INDEX(hdc);
	//pdcattr = pEntry->UserData;

	DeleteDC(hdc);
}