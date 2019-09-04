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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/ * HPEN ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/ * HBRUSH ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  scalar_t__ COLORREF ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateCompatibleBitmap (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateSolidBrush (scalar_t__) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GM_ADVANCED ; 
 scalar_t__ GM_COMPATIBLE ; 
 scalar_t__ GetPixel (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_PEN ; 
 scalar_t__ RGB (int,int,int) ; 
 int /*<<< orphan*/  Rectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetGraphicsMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WHITENESS ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void Test_Rectangle(void)
{
    HDC hdc;
    HBITMAP hBmp;
    BOOL ret;
    HBRUSH hBrush;
    HPEN hPen;
    COLORREF color;
    
    hdc = CreateCompatibleDC(NULL);
    ok(hdc != NULL, "Failed to create the DC!\n");
    hBmp = CreateCompatibleBitmap(hdc, 4, 4);
    ok(hBmp != NULL, "Failed to create the Bitmap!\n");
    hBmp = SelectObject(hdc, hBmp);
    ok(hBmp != NULL, "Failed to select the Bitmap!\n");
    
    hBrush = CreateSolidBrush(RGB(0, 0, 0));
    ok(hBrush != NULL, "Failed to create a solid brush!\n");
    hBrush = SelectObject(hdc, hBrush);
    ok(hBrush != NULL, "Failed to select the brush!\n");
    
    /* Blank the bitmap */
    ret = BitBlt(hdc, 0, 0, 4, 4, NULL, 0, 0, WHITENESS);
    ok(ret, "BitBlt failed to blank the bitmap!\n");
    
    /* Try inverted rectangle coordinates */
    ret = Rectangle(hdc, 0, 2, 2, 0);
    ok(ret, "Rectangle failed!");
    color = GetPixel(hdc, 0, 0);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 2, 2);
    ok( color == RGB(255, 255, 255), "Expected 0x00FFFFFF, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 0, 2);
    ok( color == RGB(255, 255, 255), "Expected 0x00FFFFFF, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 2, 0);
    ok( color == RGB(255, 255, 255), "Expected 0x00FFFFFF, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 1, 1);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);

    ret = BitBlt(hdc, 0, 0, 4, 4, NULL, 0, 0, WHITENESS);
    ok(ret, "BitBlt failed to blank the bitmap!\n");
    /* Try well ordered rectangle coordinates */
    ret = Rectangle(hdc, 0, 0, 2, 2);
    ok(ret, "Rectangle failed!");
    color = GetPixel(hdc, 0, 0);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 2, 2);
    ok( color == RGB(255, 255, 255), "Expected 0x00FFFFFF, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 0, 2);
    ok( color == RGB(255, 255, 255), "Expected 0x00FFFFFF, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 2, 0);
    ok( color == RGB(255, 255, 255), "Expected 0x00FFFFFF, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 1, 1);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);
    
    /* tests with NULL pen */
    hPen = SelectObject(hdc, GetStockObject(NULL_PEN));
    
    /* Blank the bitmap */
    ret = BitBlt(hdc, 0, 0, 4, 4, NULL, 0, 0, WHITENESS);
    ok(ret, "BitBlt failed to blank the bitmap!\n");
    
    ret = Rectangle(hdc, 0, 0, 3, 3);
    ok(ret, "Rectangle failed!");
    color = GetPixel(hdc, 0, 0);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 2, 2);
    ok( color == RGB(255, 255, 255), "Expected 0x00FFFFFF, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 0, 2);
    ok( color == RGB(255, 255, 255), "Expected 0x00FFFFFF, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 2, 0);
    ok( color == RGB(255, 255, 255), "Expected 0x00FFFFFF, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 1, 1);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);
    
    SelectObject(hdc, hPen);
    
    /* Same tests with GM_ADVANCED */
    ok(SetGraphicsMode(hdc, GM_ADVANCED) == GM_COMPATIBLE, "Default mode for the DC is not GM_COMPATIBLE.\n");
    
    /* Blank the bitmap */
    ret = BitBlt(hdc, 0, 0, 4, 4, NULL, 0, 0, WHITENESS);
    ok(ret, "BitBlt failed to blank the bitmap!\n");
    
    /* Try inverted rectangle coordinates */
    ret = Rectangle(hdc, 0, 2, 2, 0);
    ok(ret, "Rectangle failed!");
    color = GetPixel(hdc, 0, 0);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 2, 2);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 0, 2);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 2, 0);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 1, 1);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);

    ret = BitBlt(hdc, 0, 0, 4, 4, NULL, 0, 0, WHITENESS);
    ok(ret, "BitBlt failed to blank the bitmap!\n");    
    /* Try well ordered rectangle coordinates */
    ret = Rectangle(hdc, 0, 0, 2, 2);
    ok(ret, "Rectangle failed!");
    color = GetPixel(hdc, 0, 0);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 2, 2);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 0, 2);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 2, 0);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);
    color = GetPixel(hdc, 1, 1);
    ok( color == RGB(0, 0, 0), "Expected 0, got 0x%08x\n", (UINT)color);
    
    
    hBmp = SelectObject(hdc, hBmp);
    hBrush = SelectObject(hdc, hBrush);
    DeleteObject(hBmp);
    DeleteObject(hBrush);
    DeleteDC(hdc);
}