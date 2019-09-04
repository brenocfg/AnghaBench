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
typedef  int /*<<< orphan*/  bi ;
struct TYPE_5__ {int biSize; int biPlanes; int biBitCount; void* biHeight; void* biWidth; } ;
struct TYPE_6__ {TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  void* INT ;
typedef  scalar_t__ HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_2__ BITMAPINFO ;

/* Variables and functions */
 scalar_t__ CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateDIBSection (scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 

__attribute__((used)) static HBITMAP
IntCreate32BppBitmap(INT cx, INT cy)
{
    HBITMAP hbm = NULL;
    BITMAPINFO bi;
    HDC hdc;
    LPVOID pvBits;

    ZeroMemory(&bi, sizeof(bi));
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = cx;
    bi.bmiHeader.biHeight = cy;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;

    hdc = CreateCompatibleDC(NULL);
    if (hdc)
    {
        hbm = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, &pvBits, NULL, 0);
        DeleteDC(hdc);
    }
    return hbm;
}