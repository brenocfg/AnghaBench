#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_4__ {int member_0; int member_1; int member_2; int member_3; int member_4; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; } ;
struct TYPE_5__ {TYPE_1__ member_0; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_2__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/ * CreateDIBSection (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static HBITMAP create_test_bitmap(HDC hdc, int bpp, UINT32 pixel1, UINT32 pixel2)
{
    HBITMAP hBitmap;
    UINT32 *buffer = NULL;
    BITMAPINFO bitmapInfo = {{sizeof(BITMAPINFOHEADER), 2, 1, 1, bpp, BI_RGB,
                                0, 0, 0, 0, 0}};

    hBitmap = CreateDIBSection(hdc, &bitmapInfo, DIB_RGB_COLORS, (void**)&buffer, NULL, 0);
    ok(hBitmap != NULL && buffer != NULL, "CreateDIBSection failed.\n");

    if(!hBitmap || !buffer)
    {
        DeleteObject(hBitmap);
        return NULL;
    }

    buffer[0] = pixel1;
    buffer[1] = pixel2;

    return hBitmap;
}