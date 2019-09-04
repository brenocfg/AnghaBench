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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  HICON ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int COLORREF ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DI_NORMAL ; 
 int /*<<< orphan*/  DrawIcon (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawIconEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetPixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPixelV (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ broken (scalar_t__) ; 
 scalar_t__ color_match (int,int) ; 
 int /*<<< orphan*/  create_test_icon (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ok (int,char*,char*,int,int,char*,int,int) ; 

__attribute__((used)) static void check_alpha_draw(HDC hdc, BOOL drawiconex, BOOL alpha, int bpp, int line)
{
    HICON hicon;
    UINT32 color[2];
    COLORREF modern_expected, legacy_expected, result;

    color[0] = 0x00A0B0C0;
    color[1] = alpha ? 0xFF000000 : 0x00000000;
    modern_expected = alpha ? 0x00FFFFFF : 0x00C0B0A0;
    legacy_expected = 0x00C0B0A0;

    hicon = create_test_icon(hdc, 2, 1, bpp, 0, color, sizeof(color));
    if (!hicon) return;

    SetPixelV(hdc, 0, 0, 0x00FFFFFF);

    if(drawiconex)
        DrawIconEx(hdc, 0, 0, hicon, 2, 1, 0, NULL, DI_NORMAL);
    else
        DrawIcon(hdc, 0, 0, hicon);

    result = GetPixel(hdc, 0, 0);
    ok (color_match(result, modern_expected) ||         /* Windows 2000 and up */
        broken(color_match(result, legacy_expected)),   /* Windows NT 4.0, 9X and below */
        "%s. Expected a close match to %06X (modern) or %06X (legacy) with %s. "
        "Got %06X from line %d\n",
        alpha ? "Alpha blending" : "Not alpha blending", modern_expected, legacy_expected,
        drawiconex ? "DrawIconEx" : "DrawIcon", result, line);
}