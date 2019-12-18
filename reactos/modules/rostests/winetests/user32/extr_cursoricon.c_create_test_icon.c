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
typedef  int /*<<< orphan*/  bitmapInfo ;
typedef  int UINT32 ;
struct TYPE_7__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int biSizeImage; int /*<<< orphan*/  biCompression; } ;
struct TYPE_9__ {TYPE_1__ bmiHeader; } ;
struct TYPE_8__ {int /*<<< orphan*/  hbmMask; int /*<<< orphan*/  hbmColor; scalar_t__ yHotspot; scalar_t__ xHotspot; int /*<<< orphan*/  fIcon; } ;
typedef  TYPE_2__ ICONINFO ;
typedef  int /*<<< orphan*/ * HICON ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_3__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  CreateBitmap (int,int,int,int,int*) ; 
 int /*<<< orphan*/  CreateDIBSection (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateIconIndirect (TYPE_2__*) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (void*,int*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HICON create_test_icon(HDC hdc, int width, int height, int bpp,
                              BOOL maskvalue, UINT32 *color, int colorSize)
{
    ICONINFO iconInfo;
    BITMAPINFO bitmapInfo;
    void *buffer = NULL;
    UINT32 mask = maskvalue ? 0xFFFFFFFF : 0x00000000;

    memset(&bitmapInfo, 0, sizeof(bitmapInfo));
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = width;
    bitmapInfo.bmiHeader.biHeight = height;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = bpp;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;
    bitmapInfo.bmiHeader.biSizeImage = colorSize;

    iconInfo.fIcon = TRUE;
    iconInfo.xHotspot = 0;
    iconInfo.yHotspot = 0;

    iconInfo.hbmMask = CreateBitmap( width, height, 1, 1, &mask );
    if(!iconInfo.hbmMask) return NULL;

    iconInfo.hbmColor = CreateDIBSection(hdc, &bitmapInfo, DIB_RGB_COLORS, &buffer, NULL, 0);
    if(!iconInfo.hbmColor || !buffer)
    {
        DeleteObject(iconInfo.hbmMask);
        return NULL;
    }

    memcpy(buffer, color, colorSize);

    return CreateIconIndirect(&iconInfo);
}