#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int bcHeight; int bcWidth; int bcBitCount; int bcPlanes; int bcSize; } ;
struct TYPE_7__ {int biHeight; int biWidth; int biBitCount; int biPlanes; int biSize; } ;
struct TYPE_9__ {TYPE_2__ bmciHeader; TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int /*<<< orphan*/  BITMAPV5HEADER ;
typedef  int /*<<< orphan*/  BITMAPV4HEADER ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_3__ BITMAPINFO ;
typedef  TYPE_3__ BITMAPCOREINFO ;
typedef  int /*<<< orphan*/  BITMAPCOREHEADER ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateDIBSection (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_bitmapinfoheadersize(void)
{
    HBITMAP hdib;
    BITMAPINFO bmi;
    BITMAPCOREINFO bci;
    HDC hdc = GetDC(0);

    memset(&bmi, 0, sizeof(BITMAPINFO));
    bmi.bmiHeader.biHeight = 100;
    bmi.bmiHeader.biWidth = 512;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biPlanes = 1;

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER) - 1;

    hdib = CreateDIBSection(hdc, &bmi, 0, NULL, NULL, 0);
    ok(hdib == NULL, "CreateDIBSection succeeded\n");

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

    SetLastError(0xdeadbeef);
    hdib = CreateDIBSection(hdc, &bmi, 0, NULL, NULL, 0);
    ok(hdib != NULL, "CreateDIBSection error %d\n", GetLastError());
    DeleteObject(hdib);

    bmi.bmiHeader.biSize++;

    SetLastError(0xdeadbeef);
    hdib = CreateDIBSection(hdc, &bmi, 0, NULL, NULL, 0);
    ok(hdib != NULL ||
       broken(!hdib), /* Win98, WinMe */
       "CreateDIBSection error %d\n", GetLastError());
    DeleteObject(hdib);

    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);

    SetLastError(0xdeadbeef);
    hdib = CreateDIBSection(hdc, &bmi, 0, NULL, NULL, 0);
    ok(hdib != NULL ||
       broken(!hdib), /* Win98, WinMe */
       "CreateDIBSection error %d\n", GetLastError());
    DeleteObject(hdib);

    bmi.bmiHeader.biSize++;

    SetLastError(0xdeadbeef);
    hdib = CreateDIBSection(hdc, &bmi, 0, NULL, NULL, 0);
    ok(hdib != NULL ||
       broken(!hdib), /* Win98, WinMe */
       "CreateDIBSection error %d\n", GetLastError());
    DeleteObject(hdib);

    bmi.bmiHeader.biSize = sizeof(BITMAPV4HEADER);

    SetLastError(0xdeadbeef);
    hdib = CreateDIBSection(hdc, &bmi, 0, NULL, NULL, 0);
    ok(hdib != NULL, "CreateDIBSection error %d\n", GetLastError());
    DeleteObject(hdib);

    bmi.bmiHeader.biSize = sizeof(BITMAPV5HEADER);

    SetLastError(0xdeadbeef);
    hdib = CreateDIBSection(hdc, &bmi, 0, NULL, NULL, 0);
    ok(hdib != NULL ||
       broken(!hdib), /* Win95 */
       "CreateDIBSection error %d\n", GetLastError());
    DeleteObject(hdib);

    memset(&bci, 0, sizeof(BITMAPCOREINFO));
    bci.bmciHeader.bcHeight = 100;
    bci.bmciHeader.bcWidth = 512;
    bci.bmciHeader.bcBitCount = 24;
    bci.bmciHeader.bcPlanes = 1;

    bci.bmciHeader.bcSize = sizeof(BITMAPCOREHEADER) - 1;

    hdib = CreateDIBSection(hdc, (BITMAPINFO *)&bci, 0, NULL, NULL, 0);
    ok(hdib == NULL, "CreateDIBSection succeeded\n");

    bci.bmciHeader.bcSize = sizeof(BITMAPCOREHEADER);

    SetLastError(0xdeadbeef);
    hdib = CreateDIBSection(hdc, (BITMAPINFO *)&bci, 0, NULL, NULL, 0);
    ok(hdib != NULL, "CreateDIBSection error %d\n", GetLastError());
    DeleteObject(hdib);

    bci.bmciHeader.bcSize++;

    hdib = CreateDIBSection(hdc, (BITMAPINFO *)&bci, 0, NULL, NULL, 0);
    ok(hdib == NULL, "CreateDIBSection succeeded\n");

    bci.bmciHeader.bcSize = sizeof(BITMAPCOREINFO);

    hdib = CreateDIBSection(hdc, (BITMAPINFO *)&bci, 0, NULL, NULL, 0);
    ok(hdib == NULL, "CreateDIBSection succeeded\n");

    ReleaseDC(0, hdc);
}