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
typedef  int /*<<< orphan*/  bmih ;
struct TYPE_5__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; scalar_t__ biSizeImage; int /*<<< orphan*/  biCompression; } ;
struct TYPE_4__ {int /*<<< orphan*/  forecol; int /*<<< orphan*/  hatchstyle; int /*<<< orphan*/  backcol; } ;
typedef  scalar_t__ HBITMAP ;
typedef  TYPE_1__ GpHatch ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ BITMAPINFOHEADER ;
typedef  int /*<<< orphan*/  BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 scalar_t__ CreateDIBSection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ Ok ; 
 scalar_t__ get_hatch_data (int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static HBITMAP create_hatch_bitmap(const GpHatch *hatch)
{
    HBITMAP hbmp;
    BITMAPINFOHEADER bmih;
    DWORD *bits;
    int x, y;

    bmih.biSize = sizeof(bmih);
    bmih.biWidth = 8;
    bmih.biHeight = 8;
    bmih.biPlanes = 1;
    bmih.biBitCount = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = 0;

    hbmp = CreateDIBSection(0, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, (void **)&bits, NULL, 0);
    if (hbmp)
    {
        const char *hatch_data;

        if (get_hatch_data(hatch->hatchstyle, &hatch_data) == Ok)
        {
            for (y = 0; y < 8; y++)
            {
                for (x = 0; x < 8; x++)
                {
                    if (hatch_data[y] & (0x80 >> x))
                        bits[y * 8 + x] = hatch->forecol;
                    else
                        bits[y * 8 + x] = hatch->backcol;
                }
            }
        }
        else
        {
            FIXME("Unimplemented hatch style %d\n", hatch->hatchstyle);

            for (y = 0; y < 64; y++)
                bits[y] = hatch->forecol;
        }
    }

    return hbmp;
}