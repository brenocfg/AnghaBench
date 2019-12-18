#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_20__ {int /*<<< orphan*/  bmBits; int /*<<< orphan*/  bmBitsPixel; int /*<<< orphan*/  bmPlanes; int /*<<< orphan*/  bmWidthBytes; int /*<<< orphan*/  bmHeight; int /*<<< orphan*/  bmWidth; int /*<<< orphan*/  bmType; } ;
struct TYPE_19__ {int biWidth; int biHeight; } ;
struct TYPE_15__ {int member_1; int member_2; int member_3; int /*<<< orphan*/  member_0; } ;
struct TYPE_14__ {TYPE_3__ member_0; } ;
struct TYPE_13__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_7; int member_8; int member_9; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; } ;
struct TYPE_18__ {TYPE_7__ bmiHeader; TYPE_2__ member_1; TYPE_1__ member_0; } ;
struct TYPE_17__ {int member_1; int member_2; int member_3; int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_6; int member_7; int member_8; int member_9; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_5; } ;
typedef  TYPE_6__* PVOID ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int /*<<< orphan*/  DIBSECTION ;
typedef  int BYTE ;
typedef  TYPE_7__ BITMAPINFOHEADER ;
typedef  TYPE_6__ BITMAPINFO ;
typedef  TYPE_9__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  BI_RLE8 ; 
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CBM_CREATDIB ; 
 int CBM_INIT ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateDIBitmap (int /*<<< orphan*/ *,TYPE_7__*,int,int*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_PAL_COLORS ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetObject (int /*<<< orphan*/ *,int,TYPE_9__*) ; 
 int /*<<< orphan*/ * GetStockObject (int) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ghdcDIB32 ; 
 int /*<<< orphan*/ *** gpDIB32 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ***,int,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok_long (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
Test_CreateDIBitmap_CBM_CREATDIB(void)
{
    HBITMAP hbmp, hbmpOld;
    HDC hdc;
    BITMAPINFO bmi =
        {{sizeof(BITMAPINFOHEADER), 4, 4, 1, 8, BI_RGB, 0, 1, 1, 1, 0}, {{0,1,2,3}}};
    BYTE ajBits[10] = {0,1,2,3,4,5,6,7,8,9};
    BITMAP bitmap;
    struct
    {
        BITMAPINFOHEADER bmiHeader;
        WORD wColors[4];
    } bmiRLE =
    {
        {sizeof(BITMAPINFOHEADER), 8, 2, 1, 8, BI_RLE8, 20, 1, 1, 4, 0},
        {0, 1, 2, 7}
    };
    BYTE ajBitsRLE[] = {4,0,   0,2,0,1,0,2,3,1,   2,1, 2,2,   1,3,1,0,1,2, };

    hdc = CreateCompatibleDC(0);
    if (hdc == NULL)
    {
        ok(0, "CreateCompatibleDC failed. Skipping tests!\n");
        return;
    }

    SetLastError(0xbadbad00);
    hbmp = CreateDIBitmap(hdc, NULL, CBM_CREATDIB, ajBits, NULL, DIB_RGB_COLORS);
    ok(hbmp == 0, "CreateDIBitmap should fail.\n");
    ok_int(GetLastError(), 0xbadbad00);

    hbmp = CreateDIBitmap(hdc, NULL, CBM_CREATDIB, ajBits, &bmi, DIB_RGB_COLORS);
    ok(hbmp != 0, "CreateDIBitmap failed.\n");

    ok_long(GetObject(hbmp, sizeof(DIBSECTION), &bitmap), sizeof(BITMAP));
    ok_int(bitmap.bmType, 0);
    ok_int(bitmap.bmWidth, 4);
    ok_int(bitmap.bmHeight, 4);
    ok_int(bitmap.bmWidthBytes, 4);
    ok_int(bitmap.bmPlanes, 1);
    ok_int(bitmap.bmBitsPixel, 8);
    ok_ptr(bitmap.bmBits, 0);

    hbmpOld = SelectObject(hdc, hbmp);
    ok(hbmpOld != NULL, "Couldn't select the bitmap.\n");

    /* Copy it on a dib section */
    memset(gpDIB32, 0x77, sizeof(*gpDIB32));
    ok_long(BitBlt(ghdcDIB32, 0, 0, 4, 4, hdc, 0, 0, SRCCOPY), 1);
    ok_long((*gpDIB32)[0][0], 0x20100);
    ok_long((*gpDIB32)[0][1], 0x20100);
    ok_long((*gpDIB32)[0][2], 0x20100);
    ok_long((*gpDIB32)[0][3], 0x20100);

    SelectObject(hdc, hbmpOld);
    DeleteObject(hbmp);

    hbmp = CreateDIBitmap(hdc, NULL, CBM_CREATDIB | CBM_INIT, ajBits, &bmi, DIB_PAL_COLORS);
    ok(hbmp != 0, "CreateDIBitmap failed.\n");

    ok_long(GetObject(hbmp, sizeof(DIBSECTION), &bitmap), sizeof(BITMAP));
    ok_int(bitmap.bmType, 0);
    ok_int(bitmap.bmWidth, 4);
    ok_int(bitmap.bmHeight, 4);
    ok_int(bitmap.bmWidthBytes, 4);
    ok_int(bitmap.bmPlanes, 1);
    ok_int(bitmap.bmBitsPixel, 8);
    ok_ptr(bitmap.bmBits, 0);

    /* Even with CBM_INIT and lpbmih != 0, pbmi is used for the dimensions */
    hbmp = CreateDIBitmap(hdc, &bmiRLE.bmiHeader, CBM_CREATDIB | CBM_INIT, ajBits, &bmi, DIB_PAL_COLORS);
    ok(hbmp != 0, "CreateDIBitmap failed.\n");

    ok_long(GetObject(hbmp, sizeof(DIBSECTION), &bitmap), sizeof(BITMAP));
    ok_int(bitmap.bmType, 0);
    ok_int(bitmap.bmWidth, 4);
    ok_int(bitmap.bmHeight, 4);
    ok_int(bitmap.bmWidthBytes, 4);
    ok_int(bitmap.bmPlanes, 1);
    ok_int(bitmap.bmBitsPixel, 8);
    ok_ptr(bitmap.bmBits, 0);

    hbmpOld = SelectObject(hdc, hbmp);
    ok(hbmpOld != NULL, "Couldn't select the bitmap.\n");

    /* Copy it on a dib section */
    memset(gpDIB32, 0x77, sizeof(*gpDIB32));
    ok_long(BitBlt(ghdcDIB32, 0, 0, 4, 4, hdc, 0, 0, SRCCOPY), 1);
    ok_long((*gpDIB32)[0][0], 0);
    ok_long((*gpDIB32)[0][1], 0);
    ok_long((*gpDIB32)[0][2], 0);
    ok_long((*gpDIB32)[0][3], 0);

    SelectObject(hdc, hbmpOld);
    DeleteObject(hbmp);

    hbmp = CreateDIBitmap(hdc, NULL, CBM_CREATDIB, ajBitsRLE, (PVOID)&bmiRLE, DIB_PAL_COLORS);
    ok(hbmp == 0, "CreateDIBitmap should fail.\n");
    hbmp = CreateDIBitmap(hdc, NULL, CBM_INIT | CBM_CREATDIB, ajBitsRLE, (PVOID)&bmiRLE, DIB_PAL_COLORS);
    ok(hbmp == 0, "CreateDIBitmap should fail.\n");

    /* Check if a 0 pixel bitmap results in the DEFAULT_BITMAP being returned */
    bmi.bmiHeader.biWidth = 0;
    bmi.bmiHeader.biHeight = 4;
    hbmp = CreateDIBitmap(hdc, &bmi.bmiHeader, CBM_CREATDIB, ajBits, &bmi, DIB_PAL_COLORS);
    ok(hbmp == GetStockObject(21), "CreateDIBitmap didn't return the default bitmap.\n");
    bmi.bmiHeader.biWidth = 23;
    bmi.bmiHeader.biHeight = 0;
    hbmp = CreateDIBitmap(hdc, &bmi.bmiHeader, CBM_CREATDIB, ajBits, &bmi, DIB_PAL_COLORS);
    ok(hbmp == GetStockObject(21), "CreateDIBitmap didn't return the default bitmap.\n");

    DeleteDC(hdc);
}