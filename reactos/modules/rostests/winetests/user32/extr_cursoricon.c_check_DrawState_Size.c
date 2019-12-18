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
typedef  int /*<<< orphan*/  color ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HICON ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int COLORREF ;
typedef  int BOOL ;

/* Variables and functions */
 int DST_ICON ; 
 int /*<<< orphan*/  DrawStateA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int GetPixel (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SetPixelV (int /*<<< orphan*/ ,int,int,int) ; 
 int color_match (int,int) ; 
 scalar_t__ create_test_icon (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void check_DrawState_Size(HDC hdc, BOOL maskvalue, UINT32 color, int bpp, HBRUSH hbr, UINT flags, int line)
{
    COLORREF result, background;
    BOOL passed[2];
    HICON hicon = create_test_icon(hdc, 1, 1, bpp, maskvalue, &color, sizeof(color));
    background = 0x00FFFFFF;
    /* Set color of the 2 pixels that will be checked afterwards */
    SetPixelV(hdc, 0, 0, background);
    SetPixelV(hdc, 2, 2, background);

    /* Let DrawState calculate the size of the icon (it's 1x1) */
    DrawStateA(hdc, hbr, NULL, (LPARAM) hicon, 0, 1, 1, 0, 0, (DST_ICON | flags ));

    result = GetPixel(hdc, 0, 0);
    passed[0] = color_match(result, background);
    result = GetPixel(hdc, 2, 2);
    passed[0] = passed[0] & color_match(result, background);

    /* Check if manually specifying the icon size DOESN'T work */

    /* IMPORTANT: For Icons, DrawState wants the size of the source image, not the
     *            size in which it should be ultimately drawn. Therefore giving
     *            width/height 2x2 if the icon is only 1x1 pixels in size should
     *            result in drawing it with size 1x1. The size parameters must be
     *            ignored if a Icon has to be drawn! */
    DrawStateA(hdc, hbr, NULL, (LPARAM) hicon, 0, 1, 1, 2, 2, (DST_ICON | flags ));

    result = GetPixel(hdc, 0, 0);
    passed[1] = color_match(result, background);
    result = GetPixel(hdc, 2, 2);
    passed[1] = passed[0] & color_match(result, background);

    if(!passed[0]&&!passed[1])
        ok (passed[1],
        "DrawState failed to draw a 1x1 Icon in the correct size, independent of the "
        "width and height settings passed to it, for Icon with: Overlaying Mask %d on "
        "Color %06X with flags %08X. Line %d\n",
        maskvalue, color, (DST_ICON | flags), line);
    else if(!passed[1])
        ok (passed[1],
        "DrawState failed to draw a 1x1 Icon in the correct size, if the width and height "
        "parameters passed to it are bigger than the real Icon size, for Icon with: Overlaying "
        "Mask %d on Color %06X with flags %08X. Line %d\n",
        maskvalue, color, (DST_ICON | flags), line);
    else
        ok (passed[0],
        "DrawState failed to draw a 1x1 Icon in the correct size, if the width and height "
        "parameters passed to it are 0, for Icon with: Overlaying Mask %d on "
        "Color %06X with flags %08X. Line %d\n",
        maskvalue, color, (DST_ICON | flags), line);
}