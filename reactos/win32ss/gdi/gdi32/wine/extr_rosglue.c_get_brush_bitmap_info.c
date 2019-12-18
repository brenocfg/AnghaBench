#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int biSize; int biBitCount; int biClrUsed; int /*<<< orphan*/  biHeight; int /*<<< orphan*/  biSizeImage; } ;
struct TYPE_7__ {TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/ * PUINT ;
typedef  TYPE_2__* PBITMAPINFO ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDIBits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NtGdiGetObjectBitmapHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 

BOOL
get_brush_bitmap_info(
    HBRUSH hbr,
    PBITMAPINFO pbmi,
    PVOID *ppvBits,
    PUINT puUsage)
{
    HBITMAP hbmp;
    HDC hdc;

    /* Call win32k to get the bitmap handle and color usage */
    hbmp = NtGdiGetObjectBitmapHandle(hbr, puUsage);
    if (hbmp == NULL)
        return FALSE;

    hdc = GetDC(NULL);
    if (hdc == NULL)
        return FALSE;

    /* Initialize the BITMAPINFO */
    ZeroMemory(pbmi, sizeof(*pbmi));
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

    /* Retrieve information about the bitmap */
    if (!GetDIBits(hdc, hbmp, 0, 0, NULL, pbmi, *puUsage))
        return FALSE;

    /* Now allocate a buffer for the bits */
    *ppvBits = HeapAlloc(GetProcessHeap(), 0, pbmi->bmiHeader.biSizeImage);
    if (*ppvBits == NULL)
        return FALSE;

    /* Retrieve the bitmap bits */
    if (!GetDIBits(hdc, hbmp, 0, pbmi->bmiHeader.biHeight, *ppvBits, pbmi, *puUsage))
    {
        HeapFree(GetProcessHeap(), 0, *ppvBits);
        *ppvBits = NULL;
        return FALSE;
    }

    /* GetDIBits doesn't set biClrUsed, but wine code needs it, so we set it */
    if (pbmi->bmiHeader.biBitCount <= 8)
    {
        pbmi->bmiHeader.biClrUsed =  1 << pbmi->bmiHeader.biBitCount;
    }

    return TRUE;
}