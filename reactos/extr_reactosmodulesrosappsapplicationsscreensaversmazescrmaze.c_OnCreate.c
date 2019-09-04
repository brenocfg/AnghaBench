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
typedef  int /*<<< orphan*/  LPCREATESTRUCT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreatePen (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_SOLID ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  ReadRegistry () ; 
 int /*<<< orphan*/  TRUE ; 
 int bw ; 
 int grid_height ; 
 int grid_width ; 
 void* hBrushDead ; 
 void* hBrushLiving ; 
 int /*<<< orphan*/  hDC ; 
 int /*<<< orphan*/  hPenWall ; 
 int rand () ; 
 int size ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 int /*<<< orphan*/  start_timer (int /*<<< orphan*/ ,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
    srand((unsigned) time(NULL));

    ReadRegistry();

    if (size < 2) {
        size = 7 + (rand() % 30);
    }
    grid_width = grid_height = size;
    bw = (size > 6 ? 3 : (size - 1) / 2);
    
#if 0
    /* FIXME Pattern brushes not yet implemented in ReactOS */
    {
        static long grayPattern [] = {
            0x55555555,
            0xaaaaaaaa,
            0x55555555,
            0xaaaaaaaa,
            0x55555555,
            0xaaaaaaaa,
            0x55555555,
            0xaaaaaaaa
        };
        static RGBQUAD argbq [] = {
            { 0, 0, 255, 0 },
            { 255, 255, 255, 0 }
        };
        BITMAPINFO *pbmi;

        pbmi = malloc(sizeof(BITMAPINFOHEADER) + sizeof(argbq) + sizeof(grayPattern));
        pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        pbmi->bmiHeader.biWidth = 8;
        pbmi->bmiHeader.biHeight = 8;
        pbmi->bmiHeader.biPlanes = 1;
        pbmi->bmiHeader.biBitCount = 1;
        pbmi->bmiHeader.biCompression = BI_RGB;
        (void) memcpy(pbmi->bmiColors, argbq, sizeof(argbq));
        (void) memcpy(pbmi->bmiColors + 2, grayPattern, sizeof(grayPattern));
        hBrushDead = CreateDIBPatternBrushPt(pbmi, DIB_RGB_COLORS);
        //    hBrushDead = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 0));
        free(pbmi);
    }
#else
    hBrushDead = CreateSolidBrush(RGB(255, 0, 0));
#endif
    hBrushLiving = CreateSolidBrush(RGB(0, 255, 0));
    hPenWall = CreatePen(PS_SOLID, 3, RGB(150, 150, 150));

    hDC = GetDC(hWnd);

    start_timer(hWnd, 1);

    return TRUE;
}