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
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateBitmap (int,int,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEFAULT_BITMAP ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 scalar_t__ GDI_HANDLE_GET_TYPE (int /*<<< orphan*/ *) ; 
 scalar_t__ GDI_OBJECT_TYPE_BITMAP ; 
 int /*<<< orphan*/ * GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdc1 ; 
 int /*<<< orphan*/  hdc2 ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
Test_Bitmap()
{
    HBITMAP hbmp, hbmpInvalid, hbmpOld;
	BYTE bmBits[4] = {0};
	HDC hdcTmp;

	hbmp = CreateBitmap(2, 2, 1, 1, &bmBits);
	hbmpInvalid = CreateBitmap(2, 2, 1, 4, &bmBits);
	if (!hbmp || !hbmpInvalid)
	{
	    printf("couldn't create bitmaps, skipping\n");
	    return;
	}

    hbmpOld = SelectObject(hdc1, hbmp);
    ok(GDI_HANDLE_GET_TYPE(hbmpOld) == GDI_OBJECT_TYPE_BITMAP, "wrong type\n");

	/* Test invalid BITMAP */
    ok(SelectObject(hdc1, hbmpInvalid) == NULL, "should fail\n");

    /* Test if we get the right bitmap back */
    hbmpOld = SelectObject(hdc1, hbmpOld);
    ok(hbmpOld == hbmp, "didn't get the right bitmap back.\n");

    /* Test selecting bitmap into 2 DCs */
    hbmpOld = SelectObject(hdc1, hbmp);
    ok(SelectObject(hdc2, hbmp) == NULL, "Should fail.\n");

    /* Test selecting same bitmap twice */
    hbmpOld = SelectObject(hdc1, hbmp);
    ok(hbmpOld == hbmp, "didn't get the right bitmap back.\n");
    SelectObject(hdc1, GetStockObject(DEFAULT_BITMAP));

    /* Test selecting and then deleting the DC */
    hdcTmp = CreateCompatibleDC(NULL);
    hbmpOld = SelectObject(hdcTmp, hbmp);
    ok(hbmpOld == GetStockObject(DEFAULT_BITMAP), "didn't get the right bitmap back.\n");
    DeleteDC(hdcTmp);
    hbmpOld = SelectObject(hdc1, hbmp);
    ok(hbmpOld == GetStockObject(DEFAULT_BITMAP), "didn't get the right bitmap back.\n");

    DeleteObject(hbmp);
    DeleteObject(hbmpInvalid);
}